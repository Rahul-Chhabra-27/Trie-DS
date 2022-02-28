#include<iostream>
#include<vector>
using namespace std;

class TrieNode {
public:
    TrieNode *links[26];
    bool flag = false;
    int cntWord = 0;
    int cntPrefix = 0;

    // checking for the entry...
    bool containsKey(char ch) {
        return (links[ch-'a'] != NULL);
    }
    void putKey(char ch,TrieNode *node) {
        links[ch-'a'] = node;
    }
    TrieNode* getNext(char ch) {
        return links[ch-'a'];
    }
    void setEnd() {
        flag = true;
    }
    bool getEnd() {
        return flag;
    }
    void incrWord() {
        cntWord++;
    }
    int getCount() {
        return cntWord;
    }
    void incrPrefix() {
        cntPrefix++;
    }
    int getPrefix(){
        return cntPrefix;
    }
};
class Trie {
private:
    TrieNode *root;
public:
    Trie() {
        root = new TrieNode();
    }
    void insertWord(string word) {
        int n = word.size();
        TrieNode *temp = root;
        for(int i = 0;i<n;i++) {
            if(!temp->containsKey(word[i])) {
                temp->putKey(word[i], new TrieNode());
            }
            temp = temp->getNext(word[i]);
            temp->incrPrefix();
        }
        temp->setEnd();
        temp->incrWord();
    }
    bool searchWord(string word) {
        int n = word.size();
        TrieNode *temp = root;
        for(int i = 0;i<n;i++) {
            if(!temp->containsKey(word[i])) {
                return false;
            }
            temp = temp->getNext(word[i]);
        }
        return temp->getEnd();
    }
    bool searchPrefix(string prefix) {
        int n = prefix.size();
        TrieNode *temp = root;
        for(int i = 0;i<n;i++) {
            if(!temp->containsKey(prefix[i])) {
                return false;
            }
            temp = temp->getNext(prefix[i]);
        }
        return true;
    }
    int countWords(string word) {
        int n = word.size();
        TrieNode *temp = root;
        for(int i = 0;i<n;i++) {
            if(!temp->containsKey(word[i])) {
                return 0;
            }
            temp = temp->getNext(word[i]);
        }
        return temp->getCount();
    }
    int countPrefix(string prefix) {
        int n = prefix.size();
        TrieNode *temp = root;
        for(int i = 0;i<n;i++) {
            if(!temp->containsKey(prefix[i])) {
                return 0;
            }
            temp = temp->getNext(prefix[i]);
        }
        return temp->getPrefix();
    }
    int distinctSubstrings(string s) {
        int n = s.size();
        int cnt = 0;
        for(int i = 0;i<n;i++) {
            TrieNode *temp = root;
            for(int j = i;j<n;j++) {
                if(!temp->containsKey(s[j])) {
                    temp->putKey(s[j],new TrieNode());
                    cnt++;
                    temp = temp->getNext(s[j]);
                    temp->setEnd();
                    continue;
                }
                temp = temp->getNext(s[j]);
            }
        }
        return cnt; 
    }
    string longestCommonWord(vector<string>& arr) {
        for(auto it: arr) {
            insertWord(it);
        }
        string ans = "";
        for(auto it : arr) {
            int n = it.size();
            TrieNode *temp = root;
            bool flag = true;
            for(int i = 0;i<n;i++) {
                if(temp->containsKey(it[i])) {
                    temp = temp->getNext(it[i]);
                    flag &= temp->getEnd();
                }
                else{
                    flag = false;
                    break;
                }
            }
            if(flag) {
                if(ans.size() == it.size() and it <  ans) {
                    ans = it;
                }
                else if(ans.size() < it.size()) {
                    ans = it;
                }
            }
        }
        return ans;
    }
};
void file_i_o()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int main(int argc, char const *argv[])
{
    file_i_o();
    int n;
    cin >> n;
    Trie *t = new Trie();
    vector<string> words(n);
    for(int i = 0;i<n;i++) {
        cin >> words[i];
    }
    cout << t->longestCommonWord(words) << "\n";
    // string toBeSearched; 
    // cin >> toBeSearched;
    // cout << t->countPrefix(toBeSearched) << "\n";
    // string s ;
    // cin >> s;
    // cout << t->distinctSubstrings(s) << "\n";
    return 0;
}