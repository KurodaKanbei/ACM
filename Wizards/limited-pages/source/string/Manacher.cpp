void Manacher(std::string s,int p[]) {
    string t = "$#";
    for (int i = 0; i < s.size(); i++) {
        t += s[i];
        t += "#";
    }
    std::vector<int> p(t.size(), 0);
    int mx = 0, id = 0;
    for (int i = 1; i < t.size(); i++) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
    }
}
