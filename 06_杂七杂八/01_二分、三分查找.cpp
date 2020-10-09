// 查找第一个相等的元素
int findFirstEqual(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] >= key)
            right = mid - 1;
        else 
            left = mid + 1;
    }
    if (left < array.length && array[left] == key)
        return left;
    return -1;
}

// 查找最后一个相等的元素
int findLastEqual(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] <= key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (right >= 0 && array[right] == key)
        return right;
    return -1;
}

浮点查找最后一个相等的元素，因为浮点区间连续，所以不需要整数一样+-1
double left=0,right=2000;
while(left+eps<=right){
      double mid = (left+right)/2;
      if(isOK(mid)) left=mid;
      else right=mid;
}
printf("%lld\n",(ll)(1000*right));

// 查找最后一个等于或者小于key的元素
int findLastEqualSmaller(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] > key)
            right = mid - 1;
        else 
            left = mid + 1;
    }
    return right;
}

// 查找最后一个小于key的元素
int findLastSmaller(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] >= key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return right;
}

// 查找第一个等于或者大于key的元素
int findFirstEqualLarger(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] >= key)
            right = mid - 1;
        else 
            left = mid + 1;
    }
    return left;
}

// 查找第一个大于key的元素
int findFirstLarger(int[] array, int key) {
    int left = 0;
    int right = array.length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] > key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}


当二分的函数值不是递增/减，而是先增后减或者先减后增时二分就挂了。此时使用三分，需要注意的是必须严格递增或递减

//当存在极小值时
while(left+eps<=right){
    double lm=left+(right-left)/3;
    double rm=right-(right-left)/3;
    if(calc(lm)>=calc(rm)) left=lm;
    else right=rm;
}
printf("%.10lf\n",calc(left));

//当存在极大值时
while(left+eps<=right){
    double lm=left+(right-left)/3;
    double rm=right-(right-left)/3;
    if(calc(lm)>=calc(rm)) right=rm;
    else left=lm;
}
printf("%.10lf\n",calc(left));




















