Summary: CernVM File System VO init scripts
Name: cvmfs-init-scripts
Version: 1.0.12
Release: 1
Source0: %{name}-%{version}.tar.gz
Group: System/Filesystems
License: Copyright (c) 2009, CERN.  Distributed unter the BSD License.
Requires: cvmfs >= 0.2.61
BuildArch: noarch
%description
VO specific scripts for CernVM-FS
See http://cernvm.cern.ch
%prep
%setup -q
%build
%install
install -c etc/cvmfs/config.d/alice.cern.ch.conf /etc/cvmfs/config.d/alice.cern.ch.conf
install -c etc/cvmfs/config.d/atlas.cern.ch.conf /etc/cvmfs/config.d/atlas.cern.ch.conf
install -c etc/cvmfs/config.d/atlas-nightlies.cern.ch.conf /etc/cvmfs/config.d/atlas-nightlies.cern.ch.conf
install -c etc/cvmfs/config.d/cms.cern.ch.conf /etc/cvmfs/config.d/cms.cern.ch.conf
install -c etc/cvmfs/config.d/grid.cern.ch.conf /etc/cvmfs/config.d/grid.cern.ch.conf
install -c etc/cvmfs/config.d/hepsoft.cern.ch.conf /etc/cvmfs/config.d/hepsoft.cern.ch.conf
install -c etc/cvmfs/config.d/hone.cern.ch.conf /etc/cvmfs/config.d/hone.cern.ch.conf
install -c etc/cvmfs/config.d/lcd.cern.ch.conf /etc/cvmfs/config.d/lcd.cern.ch.conf
%files
%defattr(-,root,root)
/etc/cvmfs/config.d/alice.cern.ch.conf
/etc/cvmfs/config.d/atlas.cern.ch.conf
/etc/cvmfs/config.d/atlas-nightlies.cern.ch.conf
/etc/cvmfs/config.d/cms.cern.ch.conf
/etc/cvmfs/config.d/grid.cern.ch.conf
/etc/cvmfs/config.d/hepsoft.cern.ch.conf
/etc/cvmfs/config.d/hone.cern.ch.conf
/etc/cvmfs/config.d/lcd.cern.ch.conf
