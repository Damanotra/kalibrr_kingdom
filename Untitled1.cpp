#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;

struct position
{
    int x;
    int y;

    bool operator==(const position &o) const
    {
        return x == o.x && y==o.y;
    }

    bool operator<(const position &o) const
    {
        return x<o.x || (x==o.x && y<o.y);
    }
};

struct hasilJelajah
{
    map<char,int> counter;
    vector<string> visited;
};

hasilJelajah jelajah(vector<string> MAP, vector<string> visited,char castle,position pos, map<char,int> counter)
{
    bool dispute = false;
    int N = MAP.size();
    int M = MAP[0].size();
    queue<position> antrian;
    antrian.push(pos);
    visited[pos.x][pos.y] = '1';
    //cout<<"mulai penjajahan"<<endl;
    while(!antrian.empty())
    {
        pos = antrian.front();
        //tetangga atas
        if(pos.x>0)
        {
            //cout<<"cek tetangga atas"<<endl;
            if(visited[pos.x-1][pos.y]=='0' && MAP[pos.x-1][pos.y]!='#')
            {
                if(MAP[pos.x-1][pos.y]!='.' || MAP[pos.x-1][pos.y]!=castle)
                {
                    dispute = true;
                }
                antrian.push({pos.x-1,pos.y});
                visited[pos.x-1][pos.y] = '1';
            }
        }

        //tetangga bawah
        if(pos.x<N-1)
        {
            //cout<<"cek tetangga bawah"<<endl;
            if(visited[pos.x+1][pos.y]=='0' && MAP[pos.x+1][pos.y]!='#')
            {
                if(MAP[pos.x+1][pos.y]!='.' || MAP[pos.x+1][pos.y]!=castle)
                {
                    dispute = true;
                }
                antrian.push({pos.x+1,pos.y});
                visited[pos.x+1][pos.y] = '1';
            }
        }
        //tetangga kiri
        if(pos.y>0)
        {
            //cout<<"cek tetangga kiri"<<endl;
            if(visited[pos.x][pos.y-1]=='0' && MAP[pos.x][pos.y-1]!='#')
            {
                if(MAP[pos.x][pos.y-1]!='.' && MAP[pos.x][pos.y-1]!=castle)
                {
                    dispute = true;
                }
                antrian.push({pos.x,pos.y-1});
                visited[pos.x][pos.y-1] = '1';
            }
        }

        //tetangga kanan
        if(pos.y<M-1)
        {
            //cout<<"cek tetangga kanan"<<endl;
            if(visited[pos.x][pos.y+1]=='0' && MAP[pos.x][pos.y+1]!='#')
            {
                if(MAP[pos.x][pos.y+1]!='.' && MAP[pos.x][pos.y+1]!=castle)
                {
                    dispute = true;
                }
                antrian.push({pos.x,pos.y+1});
                visited[pos.x][pos.y+1] = '1';
            }
        }
        antrian.pop();
    }

    if(dispute==false)
    {
        counter[castle] = counter[castle]+1;
    }
    else
    {
        counter['#'] = counter['#']+1;
    }

    hasilJelajah hasil = {counter,visited};
    return hasil;
}

int main()
{
    ifstream input ("sample.in");
    ofstream output ("output.txt");
    if(input.is_open() && output.is_open())
    {
        int T;
        string line;
        getline(input,line);
        T = stoi(line);
        //cout<<T<<endl;
        for(int t=0; t<T; t++)
        {
            map<char,int> counter =
            {
                {'a',0},
                {'b',0},
                {'c',0},
                {'d',0},
                {'e',0},
                {'f',0},
                {'g',0},
                {'h',0},
                {'i',0},
                {'j',0},
                {'k',0},
                {'l',0},
                {'m',0},
                {'n',0},
                {'o',0},
                {'p',0},
                {'q',0},
                {'r',0},
                {'s',0},
                {'t',0},
                {'u',0},
                {'v',0},
                {'w',0},
                {'x',0},
                {'y',0},
                {'z',0},
                {'#',0}, //for dispute area
            };
            getline(input,line);
            int N = stoi(line);
            getline(input,line);
            int M = stoi(line);
            cout<<N<<" "<<M<<endl;
            vector<string> MAP(N);
            for(int n=0; n<N; n++)
            {
                getline(input,line);
                MAP[n]=line;
            }
            //cout<<"file been read"<<endl;
            vector<string> visited(N);
            for(int n=0; n<N; n++)
            {
                visited[n] = "";
                for(int m=0; m<M; m++)
                {
                    visited[n] = visited[n] + "0";
                }
            }
            //cout<<"map prepared"<<endl;
            for(int n=0; n<N; n++)
            {
                for(int m=0; m<M; m++)
                {
                    if(MAP[n][m]!='#' && MAP[n][m]!='.' && visited[n][m]=='0')
                    {
                        //cout<<"checking castle "<<MAP[n][m]<<endl;
                        position pos = {n,m};
                        hasilJelajah hasil = jelajah(MAP,visited,MAP[n][m],pos,counter);
                        visited = hasil.visited;
                        counter = hasil.counter;
                    }
                }
            }

            //printing result
            map<char,int>::iterator it = counter.begin();
            while(it!=counter.end())
            {
                if(it->second!=0)
                {
                    if(it->first=='#')
                    {
                        cout<<"dispute : "<<it->second<<endl;
                    }
                    else
                    {
                        cout<<it->first<<" : "<<it->second<<endl;
                    }
                }
                it++;
            }
        }
    }
}
