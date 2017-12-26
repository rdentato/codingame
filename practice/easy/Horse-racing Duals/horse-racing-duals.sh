read N

rm -f tmp.val
m=10000001
for (( i=0; i<N; i++ )); do
    read Pi
    echo $Pi >> tmp.val
done

last_num=0
while read num
do
  let d=$num-$last_num
  let k=k+1
  #echo $d
  if (( $d < $m )); then 
      #echo "min: $d ($m) ($num - $last_num)"
      export m=$d
  fi
  last_num=$num
done <<< $(sort -n tmp.val)

echo $m