def getMin(arr, start, end):
    min_idx = start

    for i in range(start, end + 1):
        if arr[min_idx] > arr[i]:
            min_idx = i
            
    return min_idx

def printArray(arr):
    for i in range(0, len(arr)):
        print arr[i]

def selectionSort(arr, start, end):
    if start < end:
        pos = getMin(arr, start, end)
        if pos != start:
            temp = arr[start]
            arr[start] = arr[pos]
            arr[pos] = temp
        selectionSort(arr, start + 1, end)

arr = [100, 2, 67, 38, 76, 12, 50, 62, 14, 60]
selectionSort(arr, 0, len(arr)-1)
printArray(arr)