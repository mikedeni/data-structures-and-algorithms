function quickSort(arr) {
  // Base case: arrays with 0 or 1 element are already sorted
  if (arr.length <= 1) return arr;

  // Choose the pivot (e.g., the last element)
  const pivot = arr[arr.length - 1];
  const left = [];
  const right = [];

  // Partition the array into left and right
  for (let i = 0; i < arr.length - 1; i++) {
    if (arr[i] < pivot) {
      left.push(arr[i]);
    } else {
      right.push(arr[i]);
    }
  }

  // Recursively sort left and right sub-arrays and combine
  return [...quickSort(left), pivot, ...quickSort(right)];
}

// Example usage
const arr = [3, 6, 8, 10, 1, 2, 1];
console.log(quickSort(arr)); // Output: [1, 1, 2, 3, 6, 8, 10]
