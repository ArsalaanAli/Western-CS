nums = [3, 4, 6, 1, 4, 6, 123, 6, 9, 14512, 5, 23, 56, 4, 75]


def insertion(nums):
    # base case, if array is size of length 1
    if len(nums) == 1:
        return nums
    # get the last element in the array (element to be inserted)
    val = nums[-1]
    # recursive call, get the sorted array of [0 : n-1]
    nums = insertion(nums[0:len(nums)-1])

    # loop through sorted array and insert the current element
    i = 0
    while i < len(nums) and nums[i] < val:
        i += 1
    left = nums[0:i]
    right = nums[i::]

    # return the sorted array
    return left + [val] + right


print(insertion(nums))
