#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
using namespace std;

	class madness{
	public:
	int allocat(ifstream teamFile,ifstream seasonFile,ifstream tournFile);
	vector<string> teamID;
	vector<string> tournSeason,tournDay,tournWT,tournLT,tournWS,tournLS;
	vector<string> combineSeason,combineDay,combineWT,combineLT,combineWS,combineLS,combineLOC,tempVec;
	map<string,string> teams,seasons;
	map<string,float> win,lost,WP;
	string full,half;
	string* tok;
	int score,scoretemp;
	string temp,temp2,winner;
	char temp3;
	int temp4[357];
	ifstream teamFile,seasonFile,tournFile,combineFile;
	int fileRead();
	int allocat();
	void champion (string se);
	void list (string se,string te);
	void finalRecord(string se,string te);
	void mostWins(string se);
	void mostAwayWins(string se);
	void bestWinPercentage(string se);
	void mostPoints(string se);
	void largestMargin(string se);
	void fewestPointsAllowed(string se);
	void fileClose();
};
string* token(string str,char delimiter)
{
	if (str.find(delimiter) != string::npos)
		{
		int dels = 0;
		string *strArr;
		for (int i = 0; i < str.length(); i ++) {
			if (str[i] == delimiter) {
				dels++;
			}
		}
		strArr = new string[dels + 1];
		string temp;
		for (int i = 0; i < (dels + 1); i ++) {
			strArr[i] = str.substr(0, str.find(delimiter));

			temp = str.substr(str.find(delimiter) + 1, str.length());
			str = temp;
		}
		return strArr;
	} else {
		return NULL;
	}
}
string seasonCheck(map<string,string> seasons,string se)
{
	string temp;
	for(map<string,string>::iterator it=seasons.begin();it!=seasons.end();it++)
	{
		if(se==it->second)
			temp=it->first;
	}
	return temp;
}
string teamCheck(map<string,string> teams,string te)
{
	string temp2;
	for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
		{
			if(te==it->second)
			temp2=it->first;
		}
	return temp2;
}

int madness::fileRead()
			{
			teamFile.open("teams.csv");
			seasonFile.open("seasons.csv");
			tournFile.open("tourney_results.csv");
			combineFile.open("regular_tourney_combined_results.csv");
			if(!teamFile||!seasonFile||!tournFile||!combineFile)
				{
					std::cout<<"Unable to open one or More file(s)\n";
					return 0;
				}
			allocat();
			return 1;
		}
int madness::allocat()
	{
	while(getline(teamFile,full))
	{
		tok=token(full,',');
		teams[tok[0]]=tok[1];
		teamID.push_back(tok[0]);

	}
	while(getline(seasonFile,full))
	{
		tok=token(full,',');
		seasons[tok[0]]=tok[1];
	}
	while(getline(tournFile,full))
	{
		tok=token(full,',');
		tournSeason.push_back(tok[0]);
		tournDay.push_back(tok[1]);
		tournWT.push_back(tok[2]);
		tournWS.push_back(tok[3]);
		tournLT.push_back(tok[4]);
		tournLS.push_back(tok[5]);
	}
	while(getline(combineFile,full))
	{
		tok=token(full,',');
		combineSeason.push_back(tok[0]);
		combineDay.push_back(tok[1]);
		combineWT.push_back(tok[2]);
		combineWS.push_back(tok[3]);
		combineLT.push_back(tok[4]);
		combineLS.push_back(tok[5]);
		combineLOC.push_back(tok[6]);
	}
	return 0;
	}
	void madness::champion (string se)
	{
		temp=seasonCheck(seasons,se);
		for(int i=0;i<tournSeason.size();i++)
		{
		if(tournDay[i]=="154" && temp==tournSeason[i])
			for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					if(tournWT[i]==it->first)
						winner=it->second;
				}
		}
		std::cout<<"\n"<<winner<<"\n";
	}
	void madness::list (string se,string te)
	{
		temp=seasonCheck(seasons,se);
		temp2=teamCheck(teams,te);
	
		for(int i=0;i<combineDay.size();i++)
		{
		if(temp==combineSeason[i])
		{
			if(temp2==combineWT[i])
			{
					for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					if(combineLT[i]==it->first)
						combineLT[i]=it->second;
				}
					std::cout<<"W"<<" "<<combineLT[i]<<" "<<combineWS[i]<<"-"<<combineLS[i]<<"\n";
			}
				
			if(temp2==combineLT[i])
			{
				for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					if(combineWT[i]==it->first)
						combineWT[i]=it->second;
				}
				std::cout<<"L"<<" "<<combineWT[i]<<" "<<combineLS[i]<<"-"<<combineWS[i]<<"\n";
			}
		}
	}

	}
void madness::finalRecord(string se,string te)
	{
		temp=seasonCheck(seasons,se);
		temp2=teamCheck(teams,te);
		int h=0;
		int j=0;
	
		for(int i=0;i<combineDay.size();i++)
		{
			if(temp==combineSeason[i])
			{
			if(temp2==combineWT[i])
				h++;
			if(temp2==combineLT[i])
				j++;
		}
	}
		std::cout<<h<<"-"<<j<<"\n";
	}
	void madness::mostWins(string se)
		{
			for(int i=0;i<357;i++)
			{
				temp4[i]=0;
			}
			temp=seasonCheck(seasons,se);
			for(int i=0;i<combineDay.size();i++)
			{
			if(temp==combineSeason[i])
				{
					int temp6=atoi(combineWT[i].c_str());
					temp4[temp6-501]++;
				}
			}
			int count=0;
			for(int i=0;i<357;i++)
				{
					if(temp4[i]>count)
					count=i;
				}
				count+=501;
				char arr[4];
				itoa(count,arr,10);
				string temp5(arr);

				for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					if(temp5==it->first)
					temp2=it->second;
				}
				std::cout<<"\n"<<temp2<<"\n";
		}
	void madness::mostAwayWins(string se)
		{
			for(int i=0;i<357;i++)
				{
					temp4[i]=0;
				}
				temp.clear();
				temp=seasonCheck(seasons,se);
				for(int i=0;i<357;i++)
					{
						temp4[i]=0;
					}
	
			for(int i=0;i<combineDay.size();i++)
				{
					if(temp==combineSeason[i])
						{
							if("A"==combineLOC[i])
								{

									int temp22=0;
									temp22=atoi(combineWT[i].c_str())-501;
									temp4[temp22]++;
								}
						}
				}
				int count2=0;
				for(int i=0;i<357;i++)
					{
						if(temp4[i]>count2)
						count2=i;
					}
				count2+=501;
				char arr2[4];
				for(int i=0;i<4;i++)
					{
						arr2[i]=NULL;
					}
				itoa(count2,arr2,10);
				string temp6=arr2;
				for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					if(temp6==it->first)
						temp2=it->second;
				}
				std::cout<<"\n"<<temp2<<"\n";
				}
	void madness::bestWinPercentage(string se)
	{
		temp=seasonCheck(seasons,se);
		for(int i=0;i<357;i++)
		{
			for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
					win[it->first]=0;
					lost[it->first]=0;					
					WP[it->first]=0;
				}
		}
		for(int i=0;i<combineDay.size();i++)
		{
			if(temp==combineSeason[i])
			{
				full=combineWT[i];
				win[full]++;
				half=combineLT[i];
				lost[half]++;
			}

		}
		for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
		{
			full=it->first;
			if((win[full]+lost[full])!=0)
			WP[full]=win[full]/(win[full]+lost[full]);
			else
				WP[full]=0;
		}
		float counter=0;
		for(map<string,float>::iterator it=WP.begin();it!=WP.end();it++)
		{
			if((it->second)>=counter)
			{
				temp2=it->first;
				counter=it->second;
			}
		}
		for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
			{
					if(temp2==it->first)
						winner=it->second;
			}
	cout<<"\n"<<winner<<"\n";
	}
	void madness::mostPoints(string se)
	{
		vector<string>SWT,SLT,SWS,SLS;
		temp=seasonCheck(seasons,se);
		for(int i=0;i<combineSeason.size();i++)
		{
			if(temp==combineSeason[i])
			{
			SWT.push_back(combineWT[i]);			
			SLT.push_back(combineLT[i]);
			SWS.push_back(combineWS[i]);
			SLS.push_back(combineLS[i]);
			}
		}
		score=0;
		temp2.clear();
		for(int i=0;i<teamID.size();i++)
			{
				scoretemp=0;
				temp2=SWT[i];
				for(int j=0;j<SWT.size();j++)
					{
					if(temp2==SLT[j])
					scoretemp+=stoi(SLS[j]);
					if(temp2==SWT[j])
					scoretemp+=stoi(SWS[j]);
					}
				if(scoretemp>score)
					score=scoretemp;
	}
	for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
		{
			if(temp2==it->first)
				winner=it->second;
		}
			cout<<"\n"<<winner<<"\n";
	}	
	void madness::fewestPointsAllowed(string se)
	{
		vector<string>SWT,SLT,SWS,SLS;
		temp=seasonCheck(seasons,se);
		for(int i=0;i<combineSeason.size();i++)
		{
			if(temp==combineSeason[i])
			{
			SWT.push_back(combineWT[i]);			
			SLT.push_back(combineLT[i]);
			SWS.push_back(combineWS[i]);
			SLS.push_back(combineLS[i]);
			}
		}
		score=0;
		temp2.clear();
		for(int i=0;i<teamID.size();i++)
			{
				scoretemp=0;
				temp2=SWT[i];
				for(int j=0;j<SWT.size();j++)
					{
					if(temp2==SLT[j])
					scoretemp+=stoi(SLS[j]);
					}
				if(scoretemp<score)
					score=scoretemp;
			}
			for(map<string,string>::iterator it=teams.begin();it!=teams.end();it++)
				{
			if(temp2==it->first)
				winner=it->second;
				}
			cout<<"\n"<<winner<<"\n";
	}
	void madness::largestMargin(string se)
	{
		vector<string>SWT,SLT,SWS,SLS;
		temp=seasonCheck(seasons,se);
		for(int i=0;i<combineSeason.size();i++)
		{
			if(temp==combineSeason[i])
			{
			SWT.push_back(combineWT[i]);			
			SLT.push_back(combineLT[i]);
			SWS.push_back(combineWS[i]);
			SLS.push_back(combineLS[i]);
			}
		}
		score=0;
		int abch=0;
		int abcl=0;
		temp2.clear();
		for(int i=0;i<teamID.size();i++)
			{
				scoretemp=0;
				temp2=SWT[i];
				for(int j=0;j<SWT.size();j++)
					{
					if(temp2==SWT[j])
					scoretemp+=stoi(SWS[j]);
					abch++;
					}
					score+=scoretemp;
			}
		int lowscore=0;
		for(int i=0;i<teamID.size();i++)
			{
				scoretemp=0;
				temp2=SWT[i];
				for(int j=0;j<SWT.size();j++)
					{
					if(temp2==SWT[j])
					scoretemp+=stoi(SWS[j]);
					abcl++;
					}
					lowscore+=scoretemp;
			}
		float margin=(score-lowscore)/(abch+abcl);
		cout<<"\n"<<margin;
	}
	void madness::fileClose(){
	teamFile.close();
	seasonFile.close();
	tournFile.close();
	combineFile.close();
	}
int main (int argc,char**argv)
{
	string arg2(argv[2]);	//converting char array to string
	string arg3(argv[3]);
	madness xyz;			//object of class madness
	if(xyz.fileRead()==0)
		return 0;
	xyz.champion(arg2);				//Question 2
	xyz.list (arg2,arg3);			//Question 3
	xyz.finalRecord(arg2,arg3);		//Question 4
	xyz.mostWins(arg2);				//Question 5
	xyz.mostAwayWins(arg2);			//Question 6
	xyz.bestWinPercentage(arg2);	//Question 7
	xyz.mostPoints(arg2);			//Question 8
	xyz.fewestPointsAllowed(arg2);	//Question 9
	xyz.fileClose();
	return 0;
}
