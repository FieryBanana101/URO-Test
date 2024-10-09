#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdint>
#include<queue>
#include<map>
#include <chrono>
#include <thread>

std::vector<std::vector<char>>grid;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<int>>dist_from_start, total_cost;
std::map<std::pair<int,int>,std::pair<int,int>>cameFrom;

void show_grid(int n){
    // show simulation grid
    std::cout << "\n    ";
    for(int i=1;i<=n;i++){
        std::cout << i << " ";
        if(i <= 9)std::cout<<' ';
    }
    std::cout << '\n';
    for(int i=0;i<n;i++){
        std::cout << i+1 << "  ";
        if(i+1<10)std::cout<<" ";
        for(int j=0;j<n;j++){
            std::cout << grid[i][j] << "  ";
        }
        std::cout << '\n';
    }
    printf("\n'S': Source, 'T': Target, 'x': Obstacle, '#': Evaluated path, '*': On queue to be evaluated\n\n");
}

void randomize_obstacle(int chances, int N){
        // randomly add obstacles
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(grid[i][j] == 'S'||grid[i][j] == 'T')continue;
                int num = rand()%100;
                if(num < chances){
                    grid[i][j] = 'x';
                }
                else{
                    grid[i][j] = '-';
                }
            }
        }
}

void construct_path(int n, int oy, int ox, int ty, int tx){
    // recover shortest path after its been found

    int curr_x = tx, curr_y = ty;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]=='S'||grid[i][j]=='T'||grid[i][j]=='x')continue;
            grid[i][j] = '-';
        }
    }
    while(true){
        if(curr_x == ox && curr_y == oy){
            break;
        }
        if(grid[curr_y][curr_x]!='S'&&grid[curr_y][curr_x]!='T'){
            grid[curr_y][curr_x] = '#';
        }
        auto next = cameFrom[std::make_pair(curr_y,curr_x)];
        curr_y = next.first;
        curr_x = next.second;
        
    }
}

bool run_A_star(int n, int delay, int oy, int ox, int ty, int tx){
    // A* implementation
    std::priority_queue<std::pair<std::pair<int,int>,std::pair<int,int>>>openSet;

    visited.assign(n+1,std::vector<bool>(n+1,0));
    visited[oy][ox] = 1;
    
    dist_from_start.assign(n+1,std::vector<int>(n+1,1e9));
    dist_from_start[oy][ox] = 0;

    total_cost.assign(n+1,std::vector<int>(n+1,1e9));
    total_cost[oy][ox] = std::abs(oy-ty)+std::abs(ox-tx);

    std::vector<std::pair<int,int>>direction = {{0,1},{0,-1},{1,0},{-1,0}};
    openSet.push(std::make_pair(std::make_pair(-total_cost[oy][ox],-total_cost[oy][ox]),std::make_pair(oy,ox)));
    
    while(!openSet.empty()){
        auto var = openSet.top();
        openSet.pop();
        int curr_y = var.second.first, curr_x = var.second.second;
        
        if(curr_x == tx && curr_y == ty){
            construct_path(n,oy,ox,ty,tx);
            return 1;
        }

        for(auto el : direction){
            if(curr_x+el.second < 0 || curr_x+el.second >= n || curr_y+el.first< 0 || curr_y+el.first>= n){
                continue;
            }
            if(grid[curr_y+el.first][curr_x+el.second] == 'x'){
                continue;
            }
            if(grid[curr_y+el.first][curr_x+el.second]!='S'&&grid[curr_y+el.first][curr_x+el.second]!='T'&&grid[curr_y+el.first][curr_x+el.second]!='#'){
                grid[curr_y+el.first][curr_x+el.second] = '*';
            }
            if( dist_from_start[curr_y][curr_x]+1 < dist_from_start[curr_y+el.first][curr_x+el.second]){
                cameFrom[std::make_pair(curr_y+el.first,curr_x+el.second)] = std::make_pair(curr_y, curr_x);
                dist_from_start[curr_y+el.first][curr_x+el.second] = dist_from_start[curr_y][curr_x]+1;
                int dist_to_target = std::abs(curr_y-ty)+std::abs(curr_x-tx);
                total_cost[curr_y+el.first][curr_x+el.second] = dist_from_start[curr_y][curr_x]+1 + dist_to_target;
                if(!visited[curr_y+el.first][curr_x+el.second]){
                    openSet.push(std::make_pair(std::make_pair(-total_cost[curr_y+el.first][curr_x+el.second],-dist_to_target),std::make_pair(curr_y+el.first,curr_x+el.second)));
                    visited[curr_y+el.first][curr_x+el.second] = 1;
                }
            }
        }
        if(grid[curr_y][curr_x]!='S'&&grid[curr_y][curr_x]!='T'){
            grid[curr_y][curr_x] = '#';
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        show_grid(n);
    }
    return 0;
}

int main(){
    //initial setup
    std::cout << "Hello welcome to A* simulator!\n\n";
    int N = 0;
    while(N<2||N>30){
        std::cout << "Please enter a grid size (2-30): ";
        std::cin>>N;
        if(N < 2 || N > 30){
            std::cout << N << " Please enter a number within the range of (5-50)!\n\n";
        }
    }
    printf("\n%d x %d grid:\n",N,N);
    grid.assign(N, std::vector<char>(N,'-'));
    show_grid(N);
    int ox=-1,oy=-1,tx=-1,ty=-1;
    //get source position
    while(true){
        printf("Source/origin position [x,y] (example: 5 10): ");
        std::cin >> ox >> oy;
        if(ox < 1 || oy < 1 || ox > N || oy > N){
            printf("Position is out of range.\n\n");
            continue;
        }
        break;
    }

    // get target position
    while(true){
        printf("Target position [x,y] (example: 5 10): ");
        std::cin >> tx >> ty;
        if(tx < 1 || ty < 1 || tx > N || ty > N){
            printf("Position is out of range.\n\n");
            continue;
        }
        if(tx == ox && ty == oy){
            printf("This position is already the origin.\n");
            continue;
        }
        break;
    }
    grid[oy-1][ox-1] = 'S';
    grid[ty-1][tx-1] = 'T';
    show_grid(N);
    bool found_path = 0;

    // allow user to add obstacle, manually or automatically (randomly)
    while(true){
        std::cout << "\nAdd obstacles?\n- 'manual' to add or remove obstacles manually\n- 'auto' to randomize obstacles [will overwrite existing obstacles]\n- 'run' to run simulation\n";
        std::string choice = "";
        std::cout << ">> ";
        std::cin>>choice;
        if(choice != "manual" && choice != "auto" && choice != "run"){
            std::cout << "Invalid command.\n";
            continue;
        }
        if(choice == "manual"){
            show_grid(N);
            std::cout << "\nPlease enter obstacle postion [x y] (example: 2 5)\nyou can remove existing obstacle by choosing its position\nplease input '0 0' when you are done\n";
            while(true){
                std::cout << "\n: ";
                int posx = -1, posy = -1;
                std::cin >> posx >> posy;
                if(posx==0&&posy==0){
                    break;
                }
                if(posx < 1 || posx > N || posy < 1 || posy > N || (posy==ty&&posx==tx) || (posy==oy&&posx==ox)){
                    std::cout << "Invalid position!\n";
                    continue;
                }
                if(grid[posy-1][posx-1]=='x'){
                     grid[posy-1][posx-1] = '-';
                     show_grid(N);
                    printf("removed obstacle at %d %d\n",posx,posy);
                }
                else{
                    grid[posy-1][posx-1] = 'x';
                    show_grid(N);
                    printf("added obstacle at %d %d\n",posx,posy);
                }
                printf("please input '0 0' when you are done\n");
            }
            std::cout << '\n';
            show_grid(N);
        }

        else if(choice == "auto"){
            randomize_obstacle(20, N);
            show_grid(N);
        }

        else{
            //call algorithm implementation
            found_path = run_A_star(N, std::min(200,3000/N), oy-1, ox-1, ty-1, tx-1);
            break;
        }
    }

    // handle result
    if(found_path){
        printf("------------------------------------\n\nShortest path has been found! (shortest path is marked with '#')\n");
    }
    else{
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(grid[i][j]=='S'||grid[i][j]=='T'||grid[i][j]=='x')continue;
                grid[i][j] = '-';
            }
        }
        printf("\nNo path exist between source and target!\n");
    }
    show_grid(N);


}
