void setup()
{
    Serial.begin(9600);
    Serial.println("START");
}

void loop()
{
    while(Serial.available()) {
        Serial.println(Serial.readString());
    }
}
