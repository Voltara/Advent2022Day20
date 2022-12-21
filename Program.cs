using System.IO;
using System.Diagnostics;

for (int i = 0; i < 100; i++) {
    string filename = $"inputs/{i:00}";
    var input = File.ReadAllLines(filename).Select(line => Int16.Parse(line)).ToList();
    Stopwatch timer = new();
    timer.Start();
    var part1 = Solve(input, 1, 1);
    var part2 = Solve(input, 10, 811589153);
    timer.Stop();
    var elapsed = (double) timer.ElapsedTicks / Stopwatch.Frequency;
    Console.WriteLine($"{elapsed:f6} ({part1} {part2})");
}

long Solve(List<short> input, int rounds, long key)
{
    int len = input.Count, mod = len - 1;
    var indices = Enumerable.Range(0, input.Count).Select(x => (short) x).ToList();
    var offsets = input.Select(x => (short) (((x * key % mod) + mod) % mod)).ToList();

    for (int round = 0; round < rounds; round++) {
        for (short i = 0; i < len; i++) {
            int pos = indices.IndexOf(i);
            indices.RemoveAt(pos);
            pos = (pos + offsets[i]) % mod;
            indices.Insert(pos, i);
        }
    }

    long answer = 0;
    int start = indices.IndexOf((short) input.IndexOf(0));
    for (int i = 1000; i <= 3000; i += 1000) {
        answer += input[indices[(start + i) % len]];
    }
    answer *= key;

    return answer;
}
