

if [ $# -gt 2 ]
then
    echo "valid input, please input a int num "
elif [ $# == 0 ]
then
    cd /home/weiaoxin/hybrid-memory/gem5
    sudo build/X86/gem5.opt configs/example/fs.py  --cpu-type=TimingSimpleCPU  --kernel=/home/weiaoxin/sim/output/build/linux-4.19.72/vmlinux \
    --disk-image=/home/weiaoxin/sim/output/rootfs.ext4 --command-line="earlyprintk=ttyS0 console=ttyS0,115200n8 lpj=7999923 root=/dev/sda"
else
    cd /home/weiaoxin/hybrid-memory/test
    sudo build/X86/gem5.opt configs/example/fs.py  --cpu-type=TimingSimpleCPU  --kernel=/home/weiaoxin/sim/output/build/linux-4.19.72/vmlinux \
    --disk-image=/home/weiaoxin/sim/output/rootfs.ext4 --command-line="earlyprintk=ttyS0 console=ttyS0,115200n8 lpj=7999923 root=/dev/sda" \
    --mem-type=NVMainMemory --nvmain-config=../nvmain/Config/Hybrid_example.config>test.out
fi