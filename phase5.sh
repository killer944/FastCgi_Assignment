# PID=`ps -eaf | grep out | grep -v grep | awk '{print $2}'`
# if [[ "" !=  "$PID" ]]; then
#   echo "killing $PID"
#   kill -9 $PID
# fi
gcc main.c $(mysql_config --libs) -o out $(mysql_config --cflags) -lfcgi -ggdb -O3 -lmemcached -lpthread -lodbc -lconfig
spawn-fcgi -a 127.0.0.1 -p 2016 out