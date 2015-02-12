Summary: General Long Baseline Experiment Simulator (GLoBES)
%define rel 0

%define version 3.0.11
%define pkgname globes
%define prefix /usr/local

%define lt_release @LT_RELEASE@
%define lt_version @LT_CURRENT@.@LT_REVISION@.@LT_AGE@

%define configure_args  

Name: %{pkgname}
Version: %{version}
Release: %{rel}

Copyright: GPL
Group: Science/Research
Source: %{pkgname}-%{version}.tar.gz

Buildroot: /tmp/%{pkgname}-root
URL: http://www.mpi-hd.mpg.de/lin/globes/
Prefix: %{prefix}
BuildArchitectures: x86_64
Packager: The GLoBES Team <globes@mpi-hd.mpg.de>
Vendor: The GLoBES Team


%description
GLoBES is a collection of numerical routines for the simulation
and analysis of neutrino oscillation experiments.


%changelog

%prep
%setup -q -n %{pkgname}-%{version}
#%patch

%build
CFLAGS="$RPM_OPT_FLAGS"
./configure --prefix=%{prefix}
make




%install
# To make things work with BUILDROOT
if [ "$RPM_BUILD_ROOT" != "/tmp/%{pkgname}-root" ]
then
  echo
  echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  echo @                                                                    @
  echo @  RPM_BUILD_ROOT is not what I expected.  Please clean it yourself. @
  echo @                                                                    @
  echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  echo
else
  echo Cleaning RPM_BUILD_ROOT: "$RPM_BUILD_ROOT"
  rm -rf "$RPM_BUILD_ROOT"
fi
make DESTDIR="$RPM_BUILD_ROOT" install

%clean
# Call me paranoid, but I do not want to be responsible for nuking
# someone's harddrive!
if [ "$RPM_BUILD_ROOT" != "/tmp/%{pkgname}-root" ]
then
  echo
  echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  echo @                                                                    @
  echo @  RPM_BUILD_ROOT is not what I expected.  Please clean it yourself. @
  echo @                                                                    @
  echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  echo
else
  echo Cleaning RPM_BUILD_ROOT: "$RPM_BUILD_ROOT"
  rm -rf "$RPM_BUILD_ROOT"
fi

%files

# Your application file list goes here
%{prefix}/lib/libglobes.*
%{prefix}/lib/globes
%{prefix}/bin/globes
%{prefix}/bin/globes-config
%{prefix}/include/globes
%{prefix}/share/globes
%{prefix}/share/aclocal/globes.m4


%doc {COPYING,ChangeLog,README,AUTHORS,BUGS,NEWS}  


# If you install a library
%post -p /sbin/ldconfig

# If you install a library
%postun -p /sbin/ldconfig


# end of file
