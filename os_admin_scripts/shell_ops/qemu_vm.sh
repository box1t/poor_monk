
# install
sudo apt install qemu-system
sudo apt install virt-manager
sudo systemctl start libvirtd
sudo usermod -aG libvirt $(whoami)
sudo systemctl status libvirtd
newgrp libvirt
ls -l /var/run/libvirt/libvirt-sock
sudo chown root:libvirt /var/run/libvirt/libvirt-sock
sudo chmod 660 /var/run/libvirt/libvirt-sock

# launch
sudo virt-manager
virt-manager

