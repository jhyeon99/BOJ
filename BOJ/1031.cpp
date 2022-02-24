#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 1234567890, SOURCE = 100, SINK = 101, MAXN = 102;
int n, m;
int capacity[MAXN][MAXN], flow[MAXN][MAXN];
int MaximumFlow()
{
	int total_flow = 0;
	while (true)
	{
		vector<int> prev(MAXN, -1);
		queue<int> q;
		prev[SOURCE] = SOURCE;
		q.push(SOURCE);
		while (!q.empty() && prev[SINK] == -1)
		{
			int curr = q.front();
			q.pop();
			for (int next = 0; next < MAXN; next++)
			{
				if (capacity[curr][next] - flow[curr][next] > 0 && prev[next] == -1)
				{
					q.push(next);
					prev[next] = curr;
				}
			}
		}
		if (prev[SINK] == -1)
			break;
		int amount = INF;
		for (int p = SINK; p != SOURCE; p = prev[p])
			amount = min(capacity[prev[p]][p] - flow[prev[p]][p], amount);
		for (int p = SINK; p != SOURCE; p = prev[p])
		{
			flow[prev[p]][p] += amount;
			flow[p][prev[p]] -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}
void ChangeFlow(int i, int j)
{
	flow[SOURCE][i]--;
	flow[i][SOURCE]++;
	flow[i][j]--;
	flow[j][i]++;
	flow[j][SINK]--;
	flow[SINK][j]++;
	vector<int> prev(MAXN, -1);
	queue<int> q;
	prev[i] = SOURCE;
	q.push(i);
	while (!q.empty() && prev[SINK] == -1)
	{
		int curr = q.front();
		q.pop();
		for (int next = 0; next < MAXN; next++)
		{
			if (curr == i && next <= j || next <= i) continue;
			if (capacity[curr][next] - flow[curr][next] > 0 && prev[next] == -1)
			{
				q.push(next);
				prev[next] = curr;
			}
		}
	}
	if (prev[SINK] == -1)
	{
		flow[SOURCE][i]++;
		flow[i][SOURCE]--;
		flow[i][j]++;
		flow[j][i]--;
		flow[j][SINK]++;
		flow[SINK][j]--;
		return;
	}
	int amount = 1;
	for (int p = SINK; p != SOURCE; p = prev[p])
	{
		flow[prev[p]][p] += amount;
		flow[p][prev[p]] -= amount;
	}
}
int main()
{
	scanf("%d %d", &n, &m);
	int sumOfNMatch = 0, sumOfMMatch = 0;
	for (int i = 0; i < n + m; i++)
	{
		int match;
		scanf("%d", &match);
		if (i < n)
		{
			capacity[SOURCE][i] = match;
			sumOfNMatch += match;
		}
		else
		{
			capacity[i][SINK] = match;
			sumOfMMatch += match;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = n; j < n + m; j++)
		{
			capacity[i][j] = 1;
		}
	}
	int maxMatchSum = max(sumOfNMatch, sumOfMMatch);
	if (maxMatchSum == MaximumFlow())
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = n; j < n + m; j++)
			{
				if (flow[i][j])
				{
					ChangeFlow(i, j);
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = n; j < n + m; j++)
			{
				printf("%d", flow[i][j]);
			}
			printf("\n");
		}
	}
	else
	{
		printf("-1\n");
	}
	return 0;
}