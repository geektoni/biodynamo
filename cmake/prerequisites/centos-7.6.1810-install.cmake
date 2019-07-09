SET(OS_SHEBANG "#!/bin/bash")
SET(ClangTools_install_command "sudo yum -y install llvm-toolset-7 llvm-toolset-7-clang-tools-extra")
SET(Git_install_command "sudo yum -y install git")
SET(Doxygen_install_command "sudo yum -y install doxygen graphviz")
SET(OpenMP_install_command "sudo yum -y install devtoolset-7-gcc*")
SET(Threads_install_command "sudo yum -y install devtoolset-7-gcc*")
SET(Numa_install_command "sudo yum -y install numactl-devel")
SET(TBB_install_command "sudo yum -y install tbb-devel")
SET(MPI_install_command "sudo yum -y install openmpi3-devel && . /etc/profile.d/modules.sh && module load mpi")
SET(MKDocs_install_command "pip install --user mkdocs mkdocs-material")
SET(Valgrind_install_command "sudo yum -y install devtoolset-7-gcc* && source scl enable devtoolset-7 bash")
SET(GLUT_install_command "sudo yum -y install freeglut-devel")
SET(PythonInterp_install_command "yum -y install https://centos7.iuscommunity.org/ius-release.rpm && yum -y install python35u python35u-devel")
SET(PythonLibs_install_command "sudo yum -y install python-devel")
SET(Coverage_install_command "sudo yum -y install lcov gcov gcovr")
SET(pip_install_command "yum -y install https://centos7.iuscommunity.org/ius-release.rpm && yum -y install python35u-pip")

