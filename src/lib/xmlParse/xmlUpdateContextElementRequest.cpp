/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "xmlParse/XmlNode.h"

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "ngsi/Request.h"
#include "convenience/UpdateContextElementRequest.h"
#include "xmlParse/xmlParse.h"
#include "xmlParse/XmlNode.h"
#include "xmlParse/xmlUpdateContextElementRequest.h"



/* ****************************************************************************
*
* attributeDomainName - 
*/
static int attributeDomainName(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got an attributeDomainName"));
   reqData->ucer.res.attributeDomainName.set(node->value());
   return 0;
}



/* ****************************************************************************
*
* contextAttribute - 
*/
static int contextAttribute(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got an attribute"));
   reqData->ucer.attributeP = new ContextAttribute();
   reqData->ucer.res.contextAttributeVector.push_back(reqData->ucer.attributeP);
   return 0;
}



/* ****************************************************************************
*
* contextAttributeName - 
*/
static int contextAttributeName(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got an attribute name: %s", node->value()));
   reqData->ucer.attributeP->name = node->value();
   return 0;
}



/* ****************************************************************************
*
* contextAttributeType - 
*/
static int contextAttributeType(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got an attribute type: %s", node->value()));
   reqData->ucer.attributeP->type = node->value();
   return 0;
}



/* ****************************************************************************
*
* contextAttributeValue - 
*/
static int contextAttributeValue(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got an attribute value: %s", node->value()));
   reqData->ucer.attributeP->value = node->value();
   return 0;
}



/* ****************************************************************************
*
* contextMetadata - 
*/
static int contextMetadata(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata"));
   reqData->ucer.metadataP = new Metadata();
   reqData->ucer.attributeP->metadataVector.push_back(reqData->ucer.metadataP);
   return 0;
}



/* ****************************************************************************
*
* contextMetadataName - 
*/
static int contextMetadataName(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata name '%s'", node->value()));
   reqData->ucer.metadataP->name = node->value();
   return 0;
}



/* ****************************************************************************
*
* contextMetadataType - 
*/
static int contextMetadataType(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata type '%s'", node->value()));
   reqData->ucer.metadataP->type = node->value();
   return 0;
}



/* ****************************************************************************
*
* contextMetadataValue - 
*/
static int contextMetadataValue(xml_node<>* node, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata value '%s'", node->value()));
   reqData->ucer.metadataP->value = node->value();
   return 0;
}



/* ****************************************************************************
*
* ucerParseVector - 
*/
XmlNode ucerParseVector[] =
{
  { "/updateContextElementRequest",                          nullTreat             },
  { "/updateContextElementRequest/attributeDomainName",      attributeDomainName   },

  { "/updateContextElementRequest/contextAttributeList",                                   nullTreat              },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute",                  contextAttribute       },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/name",             contextAttributeName   },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/type",             contextAttributeType   },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/contextValue",     contextAttributeValue  },

  { "/updateContextElementRequest/contextAttributeList/contextAttribute/metadata",                        nullTreat             },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/metadata/contextMetadata",        contextMetadata       },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/metadata/contextMetadata/name",   contextMetadataName   },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/metadata/contextMetadata/type",   contextMetadataType   },
  { "/updateContextElementRequest/contextAttributeList/contextAttribute/metadata/contextMetadata/value",  contextMetadataValue  },

  { "LAST", NULL }
};



/* ****************************************************************************
*
* ucerInit - 
*/
void ucerInit(ParseData* reqData)
{
  reqData->ucer.res.attributeDomainName.set("");

  reqData->ucer.attributeP = NULL;
  reqData->ucer.metadataP  = NULL;
}



/* ****************************************************************************
*
* ucerRelease - 
*/
void ucerRelease(ParseData* reqData)
{
  reqData->ucer.res.release();
}



/* ****************************************************************************
*
* ucerCheck - 
*/
std::string ucerCheck(ParseData* reqData, ConnectionInfo* ciP)
{
  return reqData->ucer.res.check(UpdateContextElement, ciP->outFormat, "", reqData->errorString, 0);
}



/* ****************************************************************************
*
* ucerPresent - 
*/
void ucerPresent(ParseData* reqData)
{
  reqData->ucer.res.present("");
}
