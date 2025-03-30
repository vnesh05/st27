#include <stdio.h>

int t = 0;
int interval = 5;

typedef struct{
	int time_left;
	int startTime;
	int leaveTime;
	int dead;
}tred;

void setup(int a[], tred b[]){
	int temp;
	for (int i=0; i<5; i++){
		for(int j=0; j<4; j++){
			if(b[a[j]].time_left > b[a[j + 1]].time_left)
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}


int main(){
	int i = 0;
	tred nums[5];
	int roro[5]; //q0 = round robin
	int fcfs[5]; //q1 = first come first serve
	int prsh[5]; //q2 = priority scheduler
	int sojf[5]; //q3 = shortest job first
	
	while(i<5){
		scanf(" %d",&nums[i].time_left);
		nums[i].startTime = -1;
		nums[i].dead = 0;
		i= i+ 1;	
	}
	
	i = 0;
	
	int alive = 5;
	int que = 0;
	
	for(int i=0; i<5; i++){
		roro[i] = i;
	}
	
	while(alive>0){
		
		if(que == 0){
			if(nums[roro[i]].startTime == -1){
				nums[roro[i]].startTime = t;
			}
			
			if(!nums[roro[i]].dead){
				t += interval;
				nums[roro[i]].time_left -= interval;
				if(nums[roro[i]].time_left == 0){
					nums[roro[i]].leaveTime = t;					
					nums[roro[i]].dead = 1;
					alive -= 1;
				}
				fcfs[i] = roro[i];			
			}		
		}	
		else if(que == 1){
			if(!nums[fcfs[i]].dead){
				t += interval;
				nums[fcfs[i]].time_left -= interval;
				if(nums[fcfs[i]].time_left == 0){
					nums[fcfs[i]].leaveTime = t;					
					nums[fcfs[i]].dead = 1;
					alive -= 1;
				}
				prsh[i] = fcfs[i];			
			}
		}
		else if(que == 2){
			if(!nums[prsh[i]].dead){
				t += interval;
				nums[prsh[i]].time_left -= interval;
				if(nums[prsh[i]].time_left == 0){
					nums[prsh[i]].leaveTime = t;					
					nums[prsh[i]].dead = 1;
					alive -= 1;
				}
				sojf[i] = prsh[i];			
			}
		}
		else{
			if(!nums[sojf[i]].dead){
				t += interval;
				nums[sojf[i]].time_left -= interval;
				if(nums[sojf[i]].time_left == 0){
					nums[sojf[i]].leaveTime = t;					
					nums[sojf[i]].dead = 1;
					alive -= 1;
				}
				roro[i] = sojf[i];			
			}
		}
		
		if (i == 4){
			if(que == 1){
				setup(prsh,nums);
			}
			que = (que == 3)? 0 : (que + 1);
			
			i = 0;
		}
		else{
			i = i + 1;
		}
	
	}
	return 0;
}
