#!/bin/sh
echo 'inserting module to get statistics'
sudo insmod get_statistics.ko
sudo rmmod get_statistics.ko
echo 'removed module'
