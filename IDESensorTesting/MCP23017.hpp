#ifndef MCP_23017_H
#define MCP_23017_H


#define MCP_TEST_PIN 0

struct mcp23017
{

    Adafruit_MCP23X17 mcp;
    mcp23017()
    {

    }

    void OnStart()
    {
        // uncomment appropriate mcp.begin
        if (!mcp.begin_I2C()) {
          Serial.println("Error.");
          while (1);
        }

        // configure pin for output
        mcp.pinMode(MCP_TEST_PIN, OUTPUT);

        Serial.println("MCP23017 Online.");
    }

    void OnUpdate()
    {
        //Enable expansion.
        mcp.digitalWrite(MCP_TEST_PIN, HIGH);
        delay(500);
        mcp.digitalWrite(MCP_TEST_PIN, LOW);
        delay(500);
    }

    ~mcp23017()
    {

    }
};

#endif