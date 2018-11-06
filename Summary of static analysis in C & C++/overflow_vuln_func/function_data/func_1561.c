typedef enum
{
  RESPONSETYPE_OK = 0,                /
  RESPONSETYPE_ERROR,                 /
  RESPONSETYPE_HASDATA,               /
  RESPONSETYPE_NOHANDLER,             /
  RESPONSETYPE_NOSESSION,             /
  RESPONSETYPE_BADCOMMAND,            /
  RESPONSETYPE_BADPARAMETER,          /
  RESPONSETYPE_BADPARAMETERLEN,       /
  RESPONSETYPE_MISSINGPARAMETER,      /
  RESPONSETYPE_DUPLICATEPARAMETER,    /
  RESPONSETYPE_PARAMETERCONFLICT,     /
  RESPONSETYPE_BADDEVICE,             /
  RESPONSETYPE_NVRAMERROR,            /
  RESPONSETYPE_NVRAMERRORNOACK,       /
  RESPONSETYPE_NVRAMERRORNOACK32,     /
  RESPONSETYPE_NOTI2CADDRESS,         /
  RESPONSETYPE_FIRMWAREERROR,         /
  RESPONSETYPE_DUMPINPROGRESS,        /
  RESPONSETYPE_INTERNALERROR,         /
  RESPONSETYPE_NOTIMPLEMENTED,        /
  RESPONSETYPE_PINFORMATERROR,        /
  RESPONSETYPE_PINEXISTS,             /
  RESPONSETYPE_PINNOTFOUND,           /
  RESPONSETYPE_USERACTIVE,            /
  RESPONSETYPE_USERINACTIVE,          /
  RESPONSETYPE_PARENTNOTFOUND,        /
  RESPONSETYPE_NOCHAIN,               /
  RESPONSETYPE_CAUGHTINLOOP,          /
  RESPONSETYPE_EVENTFILTERED,         /
  RESPONSETYPE_PAYLOADTOOLARGE,       /
  RESPONSETYPE_ENDOFDATA,             /
  RESPONSETYPE_RMTAUTHREJECTED,       /
  RESPONSETYPE_NVRAMVERSIONERROR,     /
  RESPONSETYPE_NOHARDWARE,            /
  RESPONSETYPE_SCHEDULERCONFLICT,     /
  RESPONSETYPE_NVRAMWRITEERROR,       /
  RESPONSETYPE_DECLINEDFILTERED,      /
  RESPONSETYPE_NECONFIGPARM,          /
  RESPONSETYPE_FLASHERASEERROR,       /
  RESPONSETYPE_FLASHWRITEERROR,       /
  RESPONSETYPE_BADNVBACKUP,           /
  RESPONSETYPE_EARLYACK,              /
  RESPONSETYPE_ALARMFILTERED,         /
  RESPONSETYPE_ACVFAILURE,            /
  RESPONSETYPE_USERCHECKSUMERROR,     /
  RESPONSETYPE_CHECKSUMERROR,         /
  RESPONSETYPE_RTCSQWFAILURE,         /
  RESPONSETYPE_PRIORITYSHUTDOWN,      /
  RESPONSETYPE_NOTMODIFIABLE,         /
  RESPONSETYPE_CANTPRESERVE,          /
  RESPONSETYPE_INPASSAGEMODE,         /
  RESPONSETYPE_LAST,
  /
  RESPONSETYPE_NOREPLY,               /
  RESPONSETYPE_TAKEABREAK,            /
  RESPONSETYPE_DPACBLOCKS,            /
  RESPONSETYPE_ACKNAKTIMEOUT,         /
  RESPONSETYPE_UNKNOWNCPUSPEED        /
}
