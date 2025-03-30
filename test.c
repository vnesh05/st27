#include <stdio.h>

int t = 0;
int interval = 5;

typedef struct {
    int time_left;
    int startTime;
    int leaveTime;
    int dead;
} tred;

void setup(int a[], tred b[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (b[a[j]].time_left > b[a[j + 1]].time_left) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int i = 0;
    tred nums[5];
    int roro[5], fcfs[5], prsh[5], sojf[5];
    int fcfs_count = 0, prsh_count = 0, sojf_count = 0;

    // Input process times
    for (i = 0; i < 5; i++) {
        scanf("%d", &nums[i].time_left);
        nums[i].startTime = -1;
        nums[i].dead = 0;
        roro[i] = i;
    }

    int alive = 5;
    int que = 0;
    i = 0;

    while (alive > 0) {
        int current_process;
        
        if (que == 0) {
            current_process = roro[i];
        } else if (que == 1) {
            current_process = fcfs[i];
        } else if (que == 2) {
            current_process = prsh[i];
        } else {
            current_process = sojf[i];
        }

        if (!nums[current_process].dead) {
            if (nums[current_process].startTime == -1) {
                nums[current_process].startTime = t;
            }

            int execution_time = (nums[current_process].time_left < interval) ? nums[current_process].time_left : interval;
            t += execution_time;
            nums[current_process].time_left -= execution_time;

            if (nums[current_process].time_left == 0) {
                nums[current_process].leaveTime = t;
                nums[current_process].dead = 1;
                alive--;
            } else {
                if (que == 0) {
                    fcfs[fcfs_count++] = current_process;
                } else if (que == 1) {
                    prsh[prsh_count++] = current_process;
                } else if (que == 2) {
                    sojf[sojf_count++] = current_process;
                } else {
                    roro[i] = current_process;
                }
            }
        }

        if (i == 4) {
            if (que == 1) {
                setup(prsh, nums, prsh_count);
            }
            que = (que == 3) ? 0 : que + 1;
            i = 0;
        } else {
            i++;
        }
    }
    
    for(int k=0; k<5; k++)
    {
      printf("Response time of process %d: %d\n",k+1,nums[k].startTime);
      printf("Tunround time of process %d: %d\n",k+1,nums[k].leaveTime);
      printf("\n");
    }
    return 0;
}
