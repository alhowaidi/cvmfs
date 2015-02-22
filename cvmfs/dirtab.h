/**
 * This file is part of the CernVM File System.
 */

#ifndef CVMFS_DIRTAB_H_
#define CVMFS_DIRTAB_H_

#include <string>
#include <vector>

#include "pathspec/pathspec.h"

namespace catalog {

/**
 * A Dirtab is handling the parsing and processing of the .cvmfsdirtab file.
 * The .cvmfsdirtab contains a list of Pathspecs that define where CernVM-FS
 * should automatically create nested catalogs. Furthermore it can contain neg-
 * ative rules to omit the automatic creation of nested catalogs in certain
 * directories.
 *
 * Example (adding a space in front of * - silence compiler warning):
 *   # this is a .cvmfsdirtab comment
 *   /software/releases/ *
 *   /conditions_data/runs/ *
 *
 *   # ignore repository directories
 *   ! *.svn
 *   ! *.git
 *
 * This .cvmfsdirtab file would generate nested catalogs in all directories
 * directly inside /software/releases/ and /conditions_data/runs/ like:
 *   /software/releases/2.1.1-2/.cvmfscatalog
 *   /software/releases/2.3.4-1/.cvmfscatalog
 *   /software/releases/3.0.0-5/.cvmfscatalog
 *   ...
 *   /conditions_data/runs/27.11.2014/.cvmfscatalog
 *   /conditions_data/runs/11.09.2013/.cvmfscatalog
 *   ...
 *
 * Note: This class does not take care of the actual creation of nested catalogs
 *       but wraps the parsing and matching of the .cvmfsdirtab file and given
 *       path strings.
 *       See: swissknife_sync.{h,cc} or t_dirtab.cc for the usage of this class.
 *
 */
class Dirtab {
 public:
  static const char kCommentMarker  = '#';
  static const char kNegationMarker = '!';

 public:
  /**
   * A Rule represents a single line from a .cvmfsdirtab file. It wraps the
   * parsed Pathspec for the path pattern in this line and stores if this Path-
   * spec should be seen as a negation rule.
   */
  struct Rule {
    Rule(const Pathspec &pathspec, const bool is_negation) :
      pathspec(pathspec), is_negation(is_negation) {}
    Pathspec  pathspec;
    bool      is_negation;
  };

  typedef std::vector<Rule> Rules;

 public:
  /**
   * Creates an empty Dirtab (mainly for testing purposes)
   */
  Dirtab();

  /**
   * Create a Dirtab from a given .cvmfsdirtab file path.
   */
  explicit Dirtab(const std::string &dirtab_path);

  /**
   * Parses the content of a .cvmfsdirtab file. This is called by the filepath-
   * constructor or can be used on an empty Dirtab for testing purposes.
   *
   * @param dirtab  a string containing the full content of a .cvmfsdirtab file
   * @return        true on successful parsing
   */
  bool Parse(const std::string &dirtab);

  /**
   * Matches a given path string against this Dirtab. The path is considered a
   * match if it matches against (at least) one positive rule and is not matched
   * by any negative rule.
   *
   * @param path  the path string to be matched against this Dirtab
   * @return      true if path string is matching this Dirtab
   */
  bool IsMatching(const std::string &path) const;

  /**
   * Matches a given path string against all negative rules in this Dirtab. This
   * bypasses the check for positive rules, thus a path string can be opposed by
   * this Dirtab while it would also not match any positive rule.
   *
   * @param path  the path string to be checked for opposition of this Dirtab
   * @return      true if (at least) one negative rule matches
   */
  bool IsOpposing(const std::string &path) const;

  const Rules& positive_rules() const { return positive_rules_; }
  const Rules& negative_rules() const { return negative_rules_; }

  size_t RuleCount() const { return NegativeRuleCount() + PositiveRuleCount(); }
  size_t NegativeRuleCount() const { return negative_rules_.size(); }
  size_t PositiveRuleCount() const { return positive_rules_.size(); }
  bool   IsValid() const { return valid_; }

 protected:
  bool Parse(FILE *dirtab_file);
  bool ParseLine(const std::string &line);
  void AddRule(const Rule &rule);

 private:
  void SkipWhitespace(
    std::string::const_iterator &itr,
    const std::string::const_iterator &end) const
  {
    for (; itr != end && *itr == ' '; ++itr) { }
  }
  bool CheckRuleValidity() const;

 private:
  bool  valid_;
  Rules positive_rules_;
  Rules negative_rules_;
};

}  // namespace catalog

#endif  // CVMFS_DIRTAB_H_

