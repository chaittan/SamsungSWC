#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A single computer configuration:
struct Configuration {
    int cpuNeeded;
    int memNeeded;
    int boardNeeded;
    int sellPrice;
};

/**
 * Recursively explores choosing up to 3 distinct configurations (each can be used
 * multiple times) to maximize revenue. Any leftover CPUs and memory chips are
 * sold at raw prices.
 *
 * @param index        which configuration we're deciding on next
 * @param usedConfigs  how many distinct configurations we've already chosen
 * @param cpusLeft     remaining CPUs
 * @param memLeft      remaining memory chips
 * @param boardsLeft   remaining boards
 * @param currentRev   revenue accumulated so far from built computers
 * @param configs      list of all available configurations
 * @param rawCpuPrice  selling price per leftover CPU
 * @param rawMemPrice  selling price per leftover memory chip
 * @param bestRevenue  reference to the running maximum revenue
 */
void backtrack(int index,
               int usedConfigs,
               int cpusLeft,
               int memLeft,
               int boardsLeft,
               int currentRev,
               const vector<Configuration>& configs,
               int rawCpuPrice,
               int rawMemPrice,
               int& bestRevenue)
{
    int n = configs.size();
    // Base case: either we considered all configs, or already used 3 distinct ones
    if (index == n || usedConfigs == 3) {
        // Sell any leftover raw materials
        int totalRev = currentRev
                     + cpusLeft * rawCpuPrice
                     + memLeft  * rawMemPrice;
        bestRevenue = max(bestRevenue, totalRev);
        return;
    }

    // 1) Option: skip this configuration entirely
    backtrack(index + 1,
              usedConfigs,
              cpusLeft, memLeft, boardsLeft,
              currentRev,
              configs,
              rawCpuPrice, rawMemPrice,
              bestRevenue);

    // 2) Option: use this configuration k times (k ≥ 1) as long as materials allow
    const Configuration& cfg = configs[index];
    int maxBuild = min({ 
        cpusLeft   / cfg.cpuNeeded,
        memLeft    / cfg.memNeeded,
        boardsLeft / cfg.boardNeeded
    });

    // If we can't build even one, skip this branch
    for (int k = 1; k <= maxBuild; ++k) {
        backtrack(index + 1,
                  usedConfigs + 1,                      // using one more distinct config
                  cpusLeft   - k * cfg.cpuNeeded,
                  memLeft    - k * cfg.memNeeded,
                  boardsLeft - k * cfg.boardNeeded,
                  currentRev + k * cfg.sellPrice,
                  configs,
                  rawCpuPrice, rawMemPrice,
                  bestRevenue);
    }
}

int solveOneCase()
{
    // Read raw‐material inventories and raw‐sell prices
    int D, E, F, d, e;
    cin >> D >> E >> F >> d >> e;

    // Read configurations
    int N;
    cin >> N;
    vector<Configuration> configs(N);
    for (int i = 0; i < N; ++i) {
        cin
          >> configs[i].cpuNeeded
          >> configs[i].memNeeded
          >> configs[i].boardNeeded
          >> configs[i].sellPrice;
    }

    int bestRevenue = 0;
    // Start the backtracking from the 0-th configuration
    backtrack(0,        // start index
              0,        // usedConfigs = 0
              D, E, F, // raw materials left
              0,        // currentRev = 0
              configs,
              d, e,
              bestRevenue);

    return bestRevenue;
}

int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int answer = solveOneCase();
        cout << "Case #" << tc << "\n"
             << answer << "\n";
    }
    return 0;
}
