echo Cleaning outdated compilation...
rm -r ../project-testing
mkdir ../project-testing
cd ../project-testing
cmake ../src
echo Building Runtime++ project...
make -j 20
echo Invoking Runtime++ project...
./runtime-project