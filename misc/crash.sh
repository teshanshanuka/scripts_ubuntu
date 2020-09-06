kdump-config show
sudo sysctl -w kernel.sysrq=1
echo "insert echo c > /proc/sysrq-trigger"
sudo -s

