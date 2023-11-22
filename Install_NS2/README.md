<div align=Center> 
    Install NS2 in Ubuntu
</div>

## install Automatically 
```
sudo apt install ns2
```
```
ns sample.tcl
```

run the file 

## Install Manually 
step 1: run the command for Update
```
sudo apt-get update
sudo apt-get dist-upgrade
sudo apt-get update
```
step 2: run the command for install NS2 Prerequisites
```
sudo apt-get install build-essential autoconf automake
sudo apt-get install tcl-dev tk-dev
sudo apt-get install build-essential autoconf automake libxmu-dev gcc g++ python2.7 python2.7-dev python-tk libxml2 libxml2-dev tcl-dev tk-dev
```
step 3: Download NS2 zib File [NS2](https://sourceforge.net/projects/nsnam/) or [stable Version]()<br>
step 4: `Extract` the .zib File <br>
step 5: Move to the .zib extracted folder in my case `Desktop` <br>
```
cd Desktop/ns-2.35
./configure
make
sudo make install
```
step 6: Add your path 
```
export NS=/path/to/ns-allinone-2.xx/ns-2.xx/
export NAM=/path/to/ns-allinone-2.xx/nam-1.xx/
```
step 7: Run the tcl file
```
ns sample.tcl
```


