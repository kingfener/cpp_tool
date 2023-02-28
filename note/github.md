# 技术日志

## github 访问

实现国内访问 github, 通过 DNS 修改的方式。
Ubuntu22.04
* S1： 获取 github dns：https://tool.chinaz.com/dns?type=a&host=github.com&ip=

* S2：ubuntu22.04 系统，使用netplan 配置网络。
  ○ sudo nano /etc/netplan/01-network-manager-all.yaml
```
# Let NetworkManager manage all devices on this>
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    enp4s0:   #配置的网卡名称
      dhcp4: no    #dhcp4关闭
      dhcp6: no    #dhcp6关闭
      addresses: [192.168.1.110/24]   #设置本机>
      #gateway4: 192.168.1.255   #设置网关
      routes:
        - to: default
          via: 192.168.1.1  # 路由（网关）
      nameservers:
        addresses: [20.205.243.166]   #设置DNS
  version: 2
```
* sudo netplan apply   （配置生效）


## mac os
* sudo vim /etc/hosts
```
# github.com :
# ref1：https://blog.csdn.net/qq_41176055/article/details/128496628
# ref2: https://blog.csdn.net/u012975252/article/details/113033239
20.205.243.166 github.com
```
* sudo killall -HUP mDNSResponder    (生效)