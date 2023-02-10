# echo $(pidof output)
# killall `pidof output`
PID=`ps -eaf | grep output | grep -v grep | awk '{print $2}'`
if [[ "" !=  "$PID" ]]; then
  echo "killing $PID"
  kill -9 $PID
fi
gcc phase4.c $(mysql_config --libs) -o output $(mysql_config --cflags) -lfcgi -ggdb -O3 -lmemcached -lpthread
spawn-fcgi -a 127.0.0.1 -p 2016 output