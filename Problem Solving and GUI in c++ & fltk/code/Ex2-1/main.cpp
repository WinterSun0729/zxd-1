//第一种方法经过优化后的时间复杂度在N(sqrt(n))
//第二种方法的时间复杂度在N(n)

#include <iostream>
#include "cmath"
using namespace std;

//函数1:因式分解
int *factorization(int num){
    int *div;
    div = new int [num+1];
    for(int i = 0; i <= num; i++) {
        div[i] = 0;
    }
    for(int i = 2;i <= num; i++){
        while(num % i == 0){
            num /= i;
            div[i] ++;
        }
    }
    return div;
}
//函数2:因子组合相乘
int *combine(int num,int *div,int &sum){
    int *div_be = new int [num];
    div_be[0] = 1;
    int j = 1;
    for(int i = 1; i <= num; i++){
        int t = 1;
        for(int i2 = 0; i2 < div[i]; i2++){
            t *= i;
            for(int i3 = 0; i3 < sum; i3++){
                div_be[j] = div_be[i3] * t;
                j++;
            }
        }
        sum = j;
    }
    return div_be;
}
//函数3:结果排序
int Partition(int *A,int low,int high){
    int pivot=A[low];//第一个元素作为基准
    while(low<high){
        while(low<high && A[high]>=pivot) high--;
        A[low]=A[high];
        while(low<high && A[low]<=pivot) low++;
        A[high]=A[low];
    }
    A[low]=pivot;

    return low;
}

void QuickSort(int *A,int low,int high){
    if(low<high){
        int pivotpos=Partition(A,low,high);
        QuickSort(A,low,pivotpos-1);
        QuickSort(A,pivotpos+1,high);
    }
}


int main()
{
    //method 1
    int num = 0;
    cin >> num;
    int k = sqrt(num);
    if(true){
        int sum = 0,p1 = 0,p2 = 0;
        int *div1,*div2;
        div1 = new int [k];//记录小于k的一般因数
        div2 = new int [k];//记录大于k的一般因数
        for(int i = 1;i <= k+1; i++){
            if(num % i == 0){
                if(i == num/i){
                    sum += 1;
                    div1[p1] = i;
                    p1++;
                }
                else{
                    sum += 2;
                    div1[p1] = i;
                    p1++;
                    div2[p2] = num/i;
                    p2++;
                }
            }
        }
        cout << sum;
        if(sum % 2 == 0){
            for(int i = 0; i < sum/2; i++){
                cout << ' ';
                cout << div1[i];
            }
            for(int i = sum/2 -1; i >= 0; i--){
                cout << ' ';
                cout << div2[i];
            }
        }
        else{
            for(int i = 0; i <= sum/2; i++){
                cout << ' ';
                cout << div1[i];
            }
            for(int i = sum/2 -1; i >= 0; i--){
                cout << ' ';
                cout << div2[i];
            }
        }

        delete [] div1;
        delete [] div2;
        cout << endl;
    }

    //method 2
    if(true){
        int *div, *div_be;
        int sum = 1;
        div = factorization(num);
        div_be = combine(num, div, sum);
        QuickSort(div_be, 1, sum-1);
        cout << sum;
        if(sum == 1)div_be[0] = 1;
        for(int i = 0; i < sum; i++){
            cout << ' ';
            cout << div_be[i];
        }
        delete [] div;
        delete [] div_be;
    }

    return 0;
}
