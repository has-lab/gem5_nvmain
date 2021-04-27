if [ $# -gt 2 ]
then
    echo "valid input, please input a int num "
elif [ $# == 0 ]
then
    cd /home/weiaoxin/hybrid-memory/gem5
    sudo build/X86/gem5.opt configs/example/se.py  --cpu-type=TimingSimpleCPU \
    -c /home/weiaoxin/hybrid-memory/reject-gem5/rejection-gem5-userland/rejection
else
    cd /home/weiaoxin/hybrid-memory/gem5
    sudo build/X86/gem5.opt configs/example/se.py  --cpu-type=TimingSimpleCPU \
    -c /home/weiaoxin/hybrid-memory/reject-gem5/rejection-gem5-userland/rejection\
     --mem-type=NVMainMemory --nvmain-config=../nvmain/Config/Hybrid_example.config>test.out
fi