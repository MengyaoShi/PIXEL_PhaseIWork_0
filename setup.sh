export XDAQ_ROOT=/opt/xdaq
export XDAQ_BASE=/opt/xdaq
export XDAQ_OS=linux
export XDAQ_PLATFORM=x86_64_slc6
export ROOTSYS=/usr/local/bin/

export XDAQ_DOCUMENT_ROOT=/opt/xdaq/htdocs
export XDAQ_SETUP_ROOT=/opt/xdaq/share
export CACTUSBIN=/opt/cactus/bin
export CACTUSLIB=/opt/cactus/lib
export CACTUSINCLUDE=/opt/cactus/include

export FECSW_BIN=/home/fectest/FEC_SW/FecSoftwareV3_0/bin
export FECSW_LIB=/home/fectest/FEC_SW/FecSoftwareV3_0/lib
## FEC SW Standalone
export FECSW_ROOT=~/FEC_SW/FecSoftwareV3_0
export ENV_CMS_TK_FEC_ROOT=${FECSW_ROOT}
export BPIX_LIB=~/FEC_SW/Pixel/BPixelTools/tools/lib
# export BPIX_CCU=~/FEC_SW/Pixel/BPixelTools/ccu/bin


export AMC13BIN=/opt/cactus/bin/amc13
export AMC13_ADDRESS_TABLE_PATH=~/AMC13/AMC13_settings
export LD_LIBRARY_PATH=${BPIX_LIB}:${FECSW_LIB}:${XDAQ_ROOT}/lib:${ROOTSYS}:${CACTUSLIB}:$LD_LIBRARY_PATH
# put /usr/bin before /usr/local/bin to use gcc4.4 and opposite for gcc4.7
#export PATH=/usr/local/bin:/usr/bin:~/bin:${FECSW_ROOT}:${XDAQ_ROOT}/bin:${CACTUSBIN}:${AMC13BIN}:$PATH
export PATH=/usr/bin:/usr/local/bin:~/bin:${FECSW_ROOT}:${XDAQ_ROOT}/bin:${CACTUSBIN}:${AMC13BIN}:$PATH
export PYTHONPATH=$HOME/CTA/SW/pychips/src:$PYTHONPATH


#export ROOTSYS=/home/fectest/root
#export BUILD_HOME=/home/fectest/FEC_mTCA

# the part below should usually not be touched
#export ENV_CMS_TK_DIAG_ROOT=$BUILD_HOME/DiagSystem
#export ENV_CMS_TK_ONLINE_ROOT=/home/fectest/FEC_SW/FecSoftwareV3_0  #$BUILD_HOME/FecSoftwareV3_0
#export ENV_CMS_TK_FEC_ROOT=$BUILD_HOME/FecSoftwareV3_0
#export ENV_CMS_TK_HAL_ROOT=$XDAQ_ROOT
#export ENV_CMS_TK_CAEN_ROOT=$XDAQ_ROOT
#export XERCESCROOT=$XDAQ_ROOT
#
#export LD_LIBRARY_PATH=${XDAQ_ROOT}/lib/:${ROOTSYS}/lib
#export LD_LIBRARY_PATH=${BUILD_HOME}/FecSoftwareV3_0/lib:${LD_LIBRARY_PATH}
#export LD_LIBRARY_PATH=${ENV_CMS_TK_DIAG_ROOT}/tools/lib:${LD_LIBRARY_PATH}
#export LD_LIBRARY_PATH=${BUILD_HOME}/pixel/lib:${LD_LIBRARY_PATH}
#export LD_LIBRARY_PATH=/usr/lib64:${LD_LIBRARY_PATH}
#export PATH=${HOME}/bin:/sbin:${ROOTSYS}/bin:${PATH}:${BUILD_HOME}/pixel/bin
#
#cd $ROOTSYS
#source bin/thisroot.sh
#cd -
#
