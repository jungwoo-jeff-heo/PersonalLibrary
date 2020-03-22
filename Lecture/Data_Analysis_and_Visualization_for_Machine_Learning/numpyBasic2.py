import numpy as np

#1. How to use universial function
# add() / multiply(), substract(), div()
# sin() / cos() / hypot()
# bitwise_and(), left_shift()
# less(), logical_not(), equal()
# maximum(), minimum(), modf()
# isinf(), infinite(), floor(), isnan()
arr1 = np.arange(20)
print('arr6:', arr1)
print('arr6 sqrt', np.sqrt(arr1))
print('arr6 exp', np.exp(arr1))

np.random.seed(12345)
x = np.random.randn(8)
y= np.random.randn(8)

print('x:', x)
print('y:', y)
print("max:", np.maximum(x, y))


#2. Where (Conditional function)
xarr = np.array([1.1, 1.2, 1.3, 1.4, 1.5])
yarr = np.array([2.1, 2.2, 2.3, 2.4, 2.5])
cond = np.array([True, False, True, True, False])

result = [(x if c else y) for c, y, x in zip(cond, yarr, xarr)]
print('result : ', result)

result2 = np.where(cond, xarr, yarr)
print('\nresult2 : ', result2)

np.random.seed(12345)
arr2 = np.random.randn(4, 4)
print('arr2 : ', arr2)
print(np.where(arr2 > 0, 2, -2)) #cond, true value, false value
print(np.where(arr2>0, 2, arr2))


#3. Math & Statistics
#sum(), mean(), cumsum(), cumprod(), std(), var(), min(), max(), argmin(), argmax()
arr3 = np.random.randn(5, 4)
print('\n', arr3)
print('mean1 : ', arr3.mean())
print('mean2 : ', np.mean(arr3))
print('sum : ', arr3.sum())
print(arr3.sum(axis=0))
print(arr3.mean(axis=1))

arr4 = np.array([0, 1, 2, 3, 4, 5, 6, 7])
print('\n', arr4.cumsum())

arr5 = np.array([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
print(arr5.cumsum(axis = 0))
print(arr5.cumprod(axis = 1)) #누적곱

arr6 = np.random.randn(100)
print('\n', arr6)
print( (arr6>0).sum() )

bools = np.array(([[False, False, True, False], [False, False, False, False,]]))
print(bools.any(axis=1))
print(bools.all(axis=0))

data = np.random.randn(10, 4)
data = data * 2
print('\ndata : ', data)
print('data[(data>3).any(axis=1)] : ', data[(data>3).any(axis=1)])


#4. Sort, Set
#unique(x), intersect1d(x, y), union1d(x, y), in1d(x, y), setdiff1d(x, y), setxor1d(x, y)
arr7 = np.random.randn(3, 3)
print('\n', arr7)
arr7.sort(axis = 1)
print(arr7)
arr7.sort(axis=0)
print(arr7)

intData = np.array([3, 3, 3, 2, 2, 1, 1, 4, 4])
values = np.array([6, 0, 0, 3, 2, 5, 6])
print('unique : ', np.unique(intData))
print('union1d : ', np.union1d(values, intData))
print('intersect1d : ', np.intersect1d(values, intData))
print('in1d : ', np.in1d(values, intData))
print('setdiff1d : ', np.setdiff1d(values, intData))
print('setxor1d : ', np.setxor1d(values, intData))
