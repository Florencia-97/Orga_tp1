# Call like bash test_time.sh name_file iterations
#Example: bash test_time.sh glider 10

for i in {1..10}
do
  (time ./conway $2 20 20 $1 -o -) > conway.stderr 2>> time_results
done
