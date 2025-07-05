import java.util.concurrent.*; // Import concurrency utilities, including ForkJoin framework

// SumTask extends RecursiveTask to perform parallel sum computation
public class SumTask extends RecursiveTask<Integer> {
    int[] arr;      // Array to sum
    int start, end; // Range of indices to sum

    // Constructor to initialize array and range
    SumTask(int[] arr, int start, int end) {
        this.arr = arr;
        this.start = start;
        this.end = end;
    }

    // The main computation performed by this task
    protected Integer compute() {
        // If the range is small enough, compute sum directly
        if (end - start <= 10) {
            int sum = 0;
            for (int i = start; i < end; i++)
                sum += arr[i]; // Add each element in the range
            return sum; // Return the computed sum
        } else {
            // Otherwise, split the task into two subtasks
            int mid = (start + end) / 2; // Find the midpoint
            SumTask left = new SumTask(arr, start, mid); // Left subtask
            SumTask right = new SumTask(arr, mid, end);  // Right subtask
            left.fork(); // Start left subtask asynchronously
            int rightResult = right.compute(); // Compute right subtask directly
            int leftResult = left.join(); // Wait for left subtask to finish and get result
            return leftResult + rightResult; // Combine results from both subtasks
        }
    }

    // Main method to test the SumTask
    public static void main(String[] args) {
        int[] data = new int[100]; // Create an array of 100 integers
        for (int i = 0; i < 100; i++) data[i] = i + 1; // Fill array with values 1 to 100

        ForkJoinPool pool = new ForkJoinPool(); // Create a ForkJoinPool
        SumTask task = new SumTask(data, 0, 100); // Create a SumTask for the whole array

        int result = pool.invoke(task); // Start the task and get the result
        System.out.println("Sum = " + result); // Print the sum (should be 5050)
    }
}
