for i in {0..50}; do
    start=$((i * 10000))
    end=$(((i + 1) * 10000))
    taskset -c $i ./solution $start $end &
done
