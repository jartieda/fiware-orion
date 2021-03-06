#ifndef CONTEXT_ATTRIBUTE_H
#define CONTEXT_ATTRIBUTE_H

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

#include "ngsi/MetadataVector.h"
#include "common/Format.h"
#include "ngsi/Request.h"
#include "parse/CompoundValueNode.h"

#define NGSI_MD_ID       "ID"
#define NGSI_MD_LOCATION "location"


/* ****************************************************************************
*
* ContextAttribute - 
*/
typedef struct ContextAttribute
{
  std::string     name;            // Mandatory
  std::string     type;            // Optional
  std::string     value;           // Mandatory
  MetadataVector  metadataVector;  // Optional

  std::string                typeFromXmlAttribute;
  orion::CompoundValueNode*  compoundValueP;

  ContextAttribute();
  ContextAttribute(ContextAttribute* caP);
  ContextAttribute(std::string _name, std::string _type, std::string _value = "");
  ContextAttribute(std::string _name, std::string _type, orion::CompoundValueNode* _compoundValueP);

  /* Grabbers for metadata to which CB gives a special semantic */
  std::string  getId();
  std::string  getLocation();

  std::string  render(Format format, std::string indent, bool comma = false);
  std::string  check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter);
  void         present(std::string indent, int ix);
  void         release(void);
  std::string  toString(void);
} ContextAttribute;

#endif
