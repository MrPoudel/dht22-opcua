/*Raspberry Pi with WiringPi
 * Author: MrPoudel
 * Version: 0.1.0
 * https://github.com/MrPoudel/dht22-opcua
 */

#include <signal.h>
#include <pthread.h>
#include "open62541.h"
#include "gpio_read.h"

UA_Boolean running = true;
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

static void connectToSensorData( UA_Server *server, void *data)
{
  UA_NodeId id1 = UA_NODEID_STRING(1, "the.humidity");
  UA_NodeId id2 = UA_NODEID_STRING(1, "the.temperature"); 
 
  UA_Double myTemp = celsius;
  UA_Double myHumidity = humidity;

  UA_Variant myVar;
  UA_Variant_init(&myVar);
  UA_Variant_setScalar(&myVar, &myTemp, &UA_TYPES[UA_TYPES_DOUBLE]);
  UA_Server_writeValue(server, id1, myVar);
  
  UA_Variant_setScalar(&myVar, &myHumidity, &UA_TYPES[UA_TYPES_DOUBLE]);
  UA_Server_writeValue(server, id2, myVar);  
}

static void addVariable_temp(UA_Server *server) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double temperature = 0.0;
    UA_Variant_setScalar(&attr.value, &temperature, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the temperature");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the temperature");
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.temperature");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the temperature");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
}
static void addVariable_humidity(UA_Server *server) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double humidity = 0.0;
    UA_Variant_setScalar(&attr.value, &humidity, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the humidity");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the humidity");
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.humidity");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the humidity");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
}

int main(void)
{
  pthread_t pth;
  int i = 0;
  pthread_create(&pth, NULL, threadFunc,NULL);

  //do opcua related stuff here
  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_ServerConfig *config = UA_ServerConfig_new_default();
  UA_Server *server = UA_Server_new(config);

  addVariable_temp(server);
  addVariable_humidity(server);
  
  //add a method that will  update the opc ua variables in it's address space
 
  UA_Server_addRepeatedCallback(server, connectToSensorData, NULL, 1000, NULL); //call every 1 sec
  UA_StatusCode retval = UA_Server_run(server, &running);
  UA_Server_delete(server);
  UA_ServerConfig_delete(config);
  // pthread_join(pth, NULL);

 return (int)retval; 

}
