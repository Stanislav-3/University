declare -i i=-1
declare -i sum=0

declare -a array
declare -i was=0


while IFS="," read -r rec_column1 rec_column2 rec_column3
do
  if test $i -eq -1; then
  	i=0
  	continue
  fi

was=0
for item in "${array[@]}"; do
    [[ $rec_column1 == "$item" ]] && echo "$rec_column1 already counted" && was=1
done

if test $was -eq 1; then
	continue
fi




  array[${#array[@]}]=$rec_column1
  sum+=$rec_column3
  i+=1
  
  echo "Record: $rec_column1"
  echo "Quantity: $rec_column2"
  echo "Price: $rec_column3"
  echo ""
  

  
done < data.csv
echo "*********************"


# i+=+1

middle_price=`expr $sum / $i`
echo "Total count: $i"
echo "Total price: $sum"
echo "Mean price: $middle_price"





