#include<fstream>
#include<iostream>
using namespace std;
struct song{
char song_name[100];
song *song_next;
song *song_prev;
};
struct playlist{
char playlist_name[100];
playlist *playlist_next;
playlist *playlist_prev;
song  *psong_next;
};
struct undo_choice{
int done;
int choice;
int opp_choice;
struct playlist *current_playlist;
struct song *current_song;
undo_choice *next;
};
int mode();
struct playlist* adder(char a[],struct playlist *playlist_head);
struct undo_choice* undo_built(struct undo_choice* undo_head,int choice);
struct undo_choice* undo_delete(struct undo_choice *undo_head);
void undo_run(struct undo_choice* undo_head,struct playlist *playlist_head);
struct playlist* add_playlist_done(struct playlist *n,struct playlist *ptr,struct playlist *playlist_head);
void add_song_done(struct song *n,struct playlist *playlist_head);
void delete_playlist_done(struct playlist *ptr,struct playlist *playlist_head);
void delete_song_done(struct playlist *ptr,struct song *ptr1);
void play_loop(struct playlist *playlist_head);
void rev(struct playlist *playlist_head);
void play_once(struct playlist *playlist_head);
void play_playlist(struct playlist *playlist_head);
void disp_playlist(struct playlist *playlist_head);
void main_menu();
void delete_song(struct playlist *playlist_head,struct undo_choice *undo_head);
struct playlist* delete_playlist(struct playlist *playlist_head);
struct playlist* check_playlist(struct playlist *playlist_head,char a[]);
void disp_all_playlist(struct playlist *playlist_head);
struct playlist* add_playlist(struct playlist *playlist_head,struct undo_choice *undo_head);
void add_song(struct playlist *playlist_head,struct undo_choice *undo_head);
void song_playlist(struct playlist *playlist_head,struct undo_choice *undo_head);
struct playlist* check_playlist(struct playlist *playlist_head,char a[]){
struct playlist *ptr=playlist_head;
int flag=0;
while(ptr!=NULL){
if(ptr->playlist_name[0]==a[0]){
for(int i=0;(a[i]!='\0'||ptr->playlist_name[i]!='\0')&&flag==0;i++){
if(a[i]!=ptr->playlist_name[i]){
flag=1;
}
}
if(flag==0){
return ptr;
}
flag=0;
}
ptr=ptr->playlist_next;
}
return NULL;
}
struct song* check_song(struct song *song_head,char a[]){
struct song *ptr=song_head;
int flag=0;
if(song_head==NULL){
return NULL;
}
do{
if(ptr->song_name[0]==a[0]){
for(int i=0;(a[i]!='\0'||ptr->song_name[i]!='\0')&&flag==0;i++){
if(a[i]!=ptr->song_name[i]){
flag=1;
}
}
if(flag==0){
return ptr;
}
else{
flag=0;
}
}
}while(ptr!=song_head);
return NULL;
}
void song_playlist(struct playlist *playlist_head,struct undo_choice *undo_head){
char a[100];
struct playlist *ptr=playlist_head;
cout<<"ENTER PLAYLIST NAME IN WHICH YOU WANT TO ENTER"<<endl;
cin>>a;
ptr=check_playlist(playlist_head,a);
if(playlist_head==NULL||ptr!=NULL){
add_song(ptr,undo_head);
}
else{
cout<<"NO SUCH PLAYLIST FOUND";
undo_head->done=0;
}
}
void add_song(struct playlist *playlist_head,struct undo_choice *undo_head){
struct song *ptr=playlist_head->psong_next;
struct song *n=new song;
int flag=0;
cout<<"ENTER SONG NAME"<<endl;
cin>>n->song_name;
if(ptr==NULL){
flag=1;
}
struct song *ptr1=check_song(ptr,n->song_name);
if(ptr1==NULL||flag==1){
undo_head->current_song=n;
undo_head->current_playlist=playlist_head;
undo_head->done=1;
add_song_done(n,playlist_head);
}
else{
undo_head->done=0;
cout<<"SAME SONG AVILABLE ALREADY"<<endl;
}
}
void add_song_done(struct song *n,struct playlist *playlist_head){
struct song *ptr=playlist_head->psong_next;
if(ptr==NULL){
n->song_next=n;
n->song_prev=n;
playlist_head->psong_next=n;
}
else{
while(ptr->song_next!=playlist_head->psong_next){
ptr=ptr->song_next;
}
ptr->song_next=n;
n->song_prev=ptr;
n->song_next=playlist_head->psong_next;
playlist_head->psong_next->song_prev=n;
}
}
struct playlist* add_playlist(struct playlist *playlist_head,struct undo_choice *undo_head){
struct playlist *n=new playlist;
struct playlist *ptr=playlist_head;
cout<<"ENTER PLAYLIST NAME"<<endl;
cin>>n->playlist_name;
undo_head->current_playlist=n;
undo_head->done=1;
playlist_head=add_playlist_done(n,ptr,playlist_head);
return playlist_head;
}
struct playlist* add_playlist_done(struct playlist *n,struct playlist *ptr,struct playlist *playlist_head){
n->playlist_next=NULL;
n->playlist_prev=NULL;
n->psong_next=NULL;
if(playlist_head==NULL){
playlist_head=n;
}
else{
while(ptr->playlist_next!=NULL){
ptr=ptr->playlist_next;
}
ptr->playlist_next=n;
n->playlist_prev=ptr;
}
return playlist_head;
}
void disp_all_playlist(struct playlist *playlist_head){
struct playlist *ptr=playlist_head;
while(ptr!=NULL){
cout<<ptr->playlist_name<<endl;;
ptr=ptr->playlist_next;
}
}
void disp_playlist(struct playlist *playlist_head){
char a[100];
cout<<"ENTER PLAYLIST NAME YOU WANT TO SEE"<<endl;
cin>>a;
struct playlist *ptr1=check_playlist(playlist_head,a);
if(ptr1!=NULL){
if(ptr1->psong_next!=NULL){
struct song *ptr=ptr1->psong_next;
cout<<"PLAYLIST:="<<ptr1->playlist_name<<endl;
do{
cout<<ptr->song_name;
cout<<endl;
ptr=ptr->song_next;
}while(ptr!=ptr1->psong_next);
}
}
else{
cout<<"NO PLAYLIST FOUND"<<endl;
}
}
struct playlist* delete_playlist(struct playlist *playlist_head,struct undo_choice *undo_head){
char a[100];
cout<<"ENTER THE LIST NAME YOU WANT TO DELETE"<<endl;
cin>>a;
struct playlist *ptr=check_playlist(playlist_head,a);
if(ptr!=NULL){
undo_head->done=1;
undo_head->current_playlist=ptr;
cout<<ptr->playlist_name<<endl;
//if(ptr==playlist_head){
delete_playlist_done(ptr,playlist_head);
//}
}
else{
undo_head->done=0;
cout<<"NO SUCH PLAYLIST EXIST"<<endl;
}
return playlist_head;
}
void delete_playlist_done(struct playlist *ptr,struct playlist *playlist_head){
cout<<ptr->playlist_name;
if(ptr==playlist_head){
ptr=ptr->playlist_next;
ptr->playlist_prev->playlist_next=NULL;
ptr->playlist_prev=NULL;
playlist_head=ptr;
}
else{
if(ptr->playlist_next==NULL){
ptr=ptr->playlist_prev;
ptr->playlist_next=NULL;
}
else{
ptr->playlist_next->playlist_prev=ptr->playlist_prev;
ptr->playlist_prev->playlist_next=ptr->playlist_next;
}
}
}
void delete_song(struct playlist *playlist_head,struct undo_choice *undo_head){
char a[100],b[100];
cout<<"ENTER THE LIST IN WHICH SONG IS PRESENT"<<endl;
cin>>a;
struct playlist *ptr=check_playlist(playlist_head,a);
if(ptr!=NULL){
cout<<"list=="<<ptr->playlist_name<<endl;
cout<<"ENTER THE NAME OF SONG YOU WANT TO DELETE"<<endl;
cin>>b;
struct song *ptr1=check_song(ptr->psong_next,b);
if(ptr1!=NULL){
undo_head->done=1;
undo_head->current_playlist=ptr;
undo_head->current_song=ptr1;
delete_song_done(ptr,ptr1);
}
else{
undo_head->done=0;
cout<<"NO SUCH SONG FOUND"<<endl;
}
}
else{
undo_head->done=0;
cout<<"NO SUCH PLAYLIST EXIST"<<endl;
}
}
void delete_song_done(struct playlist *ptr,struct song *ptr1){
{
if(ptr1==ptr->psong_next){
if(ptr1==ptr1->song_next){
ptr->psong_next=NULL;
}
else{
ptr1->song_next->song_prev=ptr1->song_prev;
ptr1->song_prev->song_next=ptr1->song_next;
ptr->psong_next=ptr->psong_next->song_next;
}
}
else{
ptr1->song_next->song_prev=ptr1->song_prev;
ptr1->song_prev->song_next=ptr1->song_next;
}
}
}
void undo_run(struct undo_choice* undo_head,struct playlist *playlist_head){
if(undo_head!=NULL){
if(undo_head->opp_choice==1){
add_playlist_done(undo_head->current_playlist,playlist_head,playlist_head);
}
if(undo_head->opp_choice==2){
add_song_done(undo_head->current_song,undo_head->current_playlist);
}
if(undo_head->opp_choice==6){
delete_playlist_done(undo_head->current_playlist,playlist_head);
}
if(undo_head->opp_choice==7){
delete_song_done(undo_head->current_playlist,undo_head->current_song);
}
}
else{
cout<<"NOTHING TO UNDO"<<endl;
}
}
void play_playlist(struct playlist* playlist_head){
cout<<"ENTER PLAYLIST NAME YOU WANT TO PLAY"<<endl;
char a[100];
cin>>a;
struct playlist *ptr;
ptr=check_playlist(playlist_head,a);
if(ptr!=NULL){
int i=mode();
    switch(i){
    case 1: play_once(ptr);
            break;
    case 2:rev(ptr);
            break;
    case 3:play_loop(ptr);
            break;
        default: cout<<"WRONG CHOICE";
    }
}
else{
cout<<"NO SUCH PLAYLIST EXIST"<<endl;
}
}
void play_once(struct playlist *playlist_head){
struct song *ptr=playlist_head->psong_next;
if(ptr!=NULL){
do{
cout<<ptr->song_name<<endl;
ptr=ptr->song_next;
}while(ptr!=playlist_head->psong_next);
}
}
void rev(struct playlist *playlist_head){
struct song *ptr=playlist_head->psong_next;
if(ptr!=NULL){
do{
cout<<ptr->song_name<<endl;
ptr=ptr->song_prev;
}while(ptr!=playlist_head->psong_next);
}
}
void play_loop(struct playlist *playlist_head){
struct song *ptr=playlist_head->psong_next;
if(ptr!=NULL){
do{
cout<<ptr->song_name<<endl;
ptr=ptr->song_next;
}while(ptr!=playlist_head->psong_next);
}
}
int mode(){
    int i;
    cout<<"PRESS 1 TO PLAY ONCE"<<endl;
    cout<<"PRESS 2 TO PLAY REVERSE "<<endl;
    cout<<"PRESS 3 TO PLAY IN LOOP"<<endl;
    cin>>i;
    return i;
}
void undo_fun(struct playlist* &playlist_head){

}
struct undo_choice* undo_built(struct undo_choice* undo_head,int choice){
undo_choice *ptr=undo_head;
if(choice==1||choice==2||choice==6||choice==7){
undo_choice *n=new undo_choice;
n->choice=choice;
if(choice==1){
n->opp_choice=6;
}
else{
if(choice==2){
n->opp_choice=7;
}
else{
if(choice==6){
n->opp_choice=1;
}
else{
if(choice==7){
n->opp_choice=2;
}
}
}
}
if(undo_head==NULL){
n->next=NULL;
undo_head=n;
}
else{
n->next=undo_head;
undo_head=n;
}
}
return undo_head;
}
/*void undo_print(struct undo_choice *undo_start){
struct undo_choice *ptr=undo_start;
while(ptr!=NULL){
cout<<ptr->playlist_data<<endl;
cout<<ptr->song_data<<endl;
cout<<ptr->choice<<endl;
ptr=ptr->next;
}
}
*/
struct undo_choice* undo_delete(struct undo_choice *undo_head){
if(undo_head!=NULL){
undo_head=undo_head->next;
return undo_head;
}
return NULL;
}
void save_fun(struct playlist *playlist_head){
struct playlist *ptr=playlist_head;
struct song *song_head=NULL;
char a[1000];
int i,j;
ofstream outfile;
outfile.open("save_data.txt");
while(ptr!=NULL){
for(i=0;ptr->playlist_name[i]!='\0';i++){
a[i]=ptr->playlist_name[i];
}
a[i]='-';
a[i+1]='\0';
song_head=ptr->psong_next;
if(song_head!=NULL){
do{
for(j=0;a[j]!='\0';j++){

}
for(i=0,j=j;song_head->song_name[i]!='\0';i++,j++){
a[j]=song_head->song_name[i];
}
a[j]='-';
a[j+1]='\0';
song_head=song_head->song_next;
}while(song_head!=ptr->psong_next);
}
//cout<<a<<endl;
outfile<<a<<endl;
ptr=ptr->playlist_next;
}
outfile.close();
}
struct playlist*  load_fun(struct playlist *head){
ifstream myReadFile;
 myReadFile.open("save_data.txt");
 char output[100];
 if (myReadFile.is_open()) {
 while (!myReadFile.eof()) {


    myReadFile >> output;
    cout<<output<<endl;
	head=adder(output,head);


 }
}
myReadFile.close();
return head;
}

struct playlist* adder(char a[],struct playlist *playlist_head){
int i,j,k=0;
struct playlist *n=new playlist;
for(i=0;a[i]!='-';i++){
n->playlist_name[i]=a[i];
}
n->playlist_name[i]='\0';
playlist_head=add_playlist_done(n,playlist_head,playlist_head);
for(int j=i+1;a[j]!='\0';j++){
if(a[j]=='-'){
k++;
}
}
//cout<<"no. of k="<<k<<endl;
struct playlist *ptr=playlist_head;
while(ptr->playlist_next!=NULL){
ptr=ptr->playlist_next;
}
while(k--){
struct song *nn=new song;
i++;
for(int c=i,p=0;a[c]!='-'&&a[c]!='\0';i++,c++,p++){
nn->song_name[p]=a[i];
}
nn->song_name[i]='\0';
add_song_done(nn,ptr);
}
return playlist_head;
}

void main_menu(){
struct playlist *playlist_start=NULL;
struct undo_choice *undo_start=NULL;
struct undo_choice *ptr=NULL;
int choice;
while(1){
cout<<"PRESS 1 TO CREAT A NEW PLAYLIST DONE"<<endl;
cout<<"PRESS 2 TO ADD NEW SONG TO PLAYLIST DONE"<<endl;
cout<<"PRESS 3 TO DISPLAY ALL PLAYLIST NAME DONE"<<endl;
cout<<"PRESS 4 TO DISPLAY SINGLE PLAYLIST DONE"<<endl;
cout<<"PRESS 5 TO EXIT DONE"<<endl;
cout<<"PRESS 6 TO DELETE PLAYLIST DONE"<<endl;
cout<<"PRESS 7 TO DELETE SONG FROM PLAYLIST DONE"<<endl;
cout<<"PRESS 8 TO PLAY A PLAYLIST"<<endl;
cout<<"PRESS 9 TO UNDO LAST ACTION"<<endl;
cout<<"PRESS 10 TO SAVE PLAYLISTS"<<endl;
cout<<"PRESS 11 TO LOAD PREVIOUS DATA"<<endl;
cin>>choice;
undo_start=undo_built(undo_start,choice);
switch(choice){
case 1: playlist_start=add_playlist(playlist_start,undo_start);
                break;
case 2: song_playlist(playlist_start,undo_start);
                break;
case 3: disp_all_playlist(playlist_start);
                break;
case 4: disp_playlist(playlist_start);
                break;
case 5: break;
case 6: playlist_start=delete_playlist(playlist_start,undo_start);
                break;
case 7: delete_song(playlist_start,undo_start);
                break;
case 8: play_playlist(playlist_start); 
                break;
case 9:	undo_run(undo_start,playlist_start);
	undo_start=undo_delete(undo_start);	
		break;
case 10: save_fun(playlist_start);
                break;
case 11: playlist_start=load_fun(playlist_start);
                break;
default: cout<<"WRONG CHOICE";
}
if(choice==5){
break;
}
if(undo_start!=NULL){
if(undo_start->done==0){
undo_start=undo_delete(undo_start);
}
}
}
}
int main(){
main_menu();
return 0;
}
