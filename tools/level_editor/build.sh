export PROJECT=SGELevelEditor
export BUILD_DIR=build
export OUT_DIR=.out

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

export Red=1
export Green=2
export Blue=6
export White=7

tput setaf $Blue; #Color Blue 
printf "========= Start generating project =========\n"
tput setaf $White; #Color White
cmake -G "MSYS Makefiles" ..
tput setaf $Blue; #Color Blue 
printf "========== Start building project ==========\n" 
tput setaf $White; #Color White
make
result=$?

if [[ ${result} -gt 0 ]]
then
    tput setaf $Red;
    printf "=============== Build faild  ===============\n" 
else 
    tput setaf $Green;
    printf "=============== Build success ==============\n" 
    cd ..
    
    printf "Deplaying files ... "
    mkdir -p ${OUT_DIR}
    cp build/${PROJECT}.exe ${OUT_DIR}/

    printf "Done\n"
    tput setaf $Green;
    printf "================ Run project ===============\n"
    tput setaf $White;
    cd ${OUT_DIR}

    printf "\n"
    ./$PROJECT.exe
    printf "\n"
    tput setaf $Green; 
    printf "================ Project End ===============\n"
    tput setaf $White;
fi
