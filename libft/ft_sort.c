
void   ft_sort(int *arr, int len)
{
  int i;
  int key;
  int j;
  
  i = 1;
  while (i < len) 
  {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key) {
       arr[j + 1] = arr[j];
       j = j - 1;
   }
   arr[j + 1] = key;
   i++;
  }
}
