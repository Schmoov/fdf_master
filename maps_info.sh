
ls maps/*.fdf | xargs -n1 awk '
	BEGIN {min = 10000; max = -10000}
	{l++}
	{for(i=1; i<=NF; i++) {if(int($i) > max) max = int($i); if(int($i) < min) min = int($i)}}
	END {print FILENAME "\t\t" l "x" NF "x" max,min}'
