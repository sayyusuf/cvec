#!/bin/bash 
R='[1;31m' #RED 
G='[1;32m' #GREEM 
Y='[1;33m' #YELLOW 
B='[1;34m' #BLUE 
D='[2K' #CLEAR 
N='[0m' #NO COLOR 
TESTSRC=$(ls *.c) 
echo "test started..." 
for src in $TESTSRC; 
do 
	rm "$src".* 2>/dev/null ; 
	echo -en "" [ $G .. $N ] $B$src $N 
	$CC $CFLAGS $EXTRAFLAGS $src -I ../ $DEPSINC -Wl,--no-as-needed $LIBPATH $DEPSLIBSPATH -Wl,--as-needed $EXLIBS -o "$src".out 2>"$src".err 
	if [ $? -ne 0 ]; then 
		echo -e "\r" [ $R CE $N ] 
	else 
		rm "$src".err; 
		STR=$((time (./"$src".out 2>"$src".err 1>"$src".log)) 2>&1) 
		RET=$? 
		echo -en $D"\r" 
		if [ $RET -eq 0 ]; then 
			echo -en "\r" [ $G OK $N ] 
		elif [ $RET -eq 2 ]; then 
			echo -en "\r" [ $Y WR $N ] 
		else 
			echo -en "\r" [ $R ER $N ] 
		fi 
		STR=$(echo $STR | tr "\n" "|") 
		echo -e "" $STR "	" $B $src $N 
	fi 
done 
echo "test finished..." 
exit 0
