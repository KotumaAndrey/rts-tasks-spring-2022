template<typename T> class Array 
{
public:
    T* content;
    long length;
    Array(T* content, long length): content(content), length(length) {}
};

template<typename TKey, typename TValue> class Node
{
public:
    TKey key;
    TValue value;
    Node* next;

    Node(TKey key, TValue value): key(key), value(value), next(NULL) {}
};

template<typename TKey, typename TValue> class Dictionary
{
private:
    Node<TKey, TValue>* first;
    long length = 0;
public:
    void Set(TKey key, TValue value);
    TValue Get(TKey key, TValue defaultValue);
    Array<TKey> AllKeys();
};

template<typename TKey, typename TValue> void Dictionary<TKey, TValue>::Set(TKey key, TValue value) {
    if(!this->first) {
        this->first = new Node<TKey, TValue>(key, value);
        this->length++;
        return;
    }

    Node<TKey, TValue>* prev;
    Node<TKey, TValue>* cur = this->first;
    while(cur) {
        if(cur->key == key) {
            cur->value = value;
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    prev->next = new Node<TKey, TValue>(key, value);
    this->length++;
}

template<typename TKey, typename TValue> TValue Dictionary<TKey, TValue>::Get(TKey key, TValue defaultValue) {
    Node<TKey, TValue>* cur = this->first;
    while(cur) {
        if(cur->key == key) {
            return cur->value;
        }
        cur = cur->next;
    }

    return defaultValue;
}

template<typename TKey, typename TValue> Array<TKey> Dictionary<TKey, TValue>::AllKeys() {
    TKey* content = new TKey[this->length];
    int i = 0;
    Node<TKey, TValue>* cur = this->first;
    while(cur) {
        content[i] = cur->key;
        cur = cur->next;
        i++;
    }
    return Array<TKey>(content, this->length);
}

Dictionary<long, long>* dict = new Dictionary<long, long>();
long steps = 1000;
bool printed = false;

void setup()
{
    Serial.begin(9600);
    Serial.println("START");
}

void loop()
{
    if(steps > 0) {;
        long temp = random(6);

        long cnt = dict->Get(temp, 0) + 1;
        dict->Set(temp, cnt);
        steps--;
    } else if(!printed) {
        Serial.println("VALUES");
        printed = true;

        Array<long> keys = dict->AllKeys();
        for(int i = 0; i < keys.length; i++) {
            long key = keys.content[i];
            Serial.print(key);
            Serial.print(" -> ");
            Serial.println(dict->Get(key, 0));
        }

        Serial.println("END");
    }
}
