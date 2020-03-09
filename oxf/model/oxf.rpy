I-Logix-RPY-Archive version 8.14.0 C++ 9810278
{ IProject 
	- _cmheader = "$Id: oxf.rpy 1.27 2007/04/06 07:14:45 ilgiga Exp $
$Revision: 1.27 $
$Locker: $

";
	- _id = GUID 2a5bf4d4-9207-4ffd-b532-e29ce78194e4;
	- _myState = 8192;
	- _properties = { IPropertyContainer 
		- Subjects = { IRPYRawContainer 
			- size = 6;
			- value = 
			{ IPropertySubject 
				- _Name = "Browser";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Settings";
						- Properties = { IRPYRawContainer 
							- size = 4;
							- value = 
							{ IProperty 
								- _Name = "ShowImplementationArgument";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowOrder";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowSourceArtifacts";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowStereotypes";
								- _Value = "Suffix";
								- _Type = Enum;
								- _ExtraTypeInfo = "No,Prefix,Suffix";
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "CG";
				- Metaclasses = { IRPYRawContainer 
					- size = 3;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Argument";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "UsageType";
								- _Value = "None";
								- _Type = Enum;
								- _ExtraTypeInfo = "Existence, Implementation, Specification, None";
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Configuration";
						- Properties = { IRPYRawContainer 
							- size = 7;
							- value = 
							{ IProperty 
								- _Name = "CM_Author";
								- _Value = "$Author";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CM_Date";
								- _Value = "$Date";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CM_Id";
								- _Value = "$Id";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CM_Log";
								- _Value = "$Log";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CM_Revision";
								- _Value = "$Revision";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CM_Source";
								- _Value = "$Source";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "LineWrapLength";
								- _Value = "120";
								- _Type = Int;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Relation";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "InlineRelationForcesAnInclude";
								- _Value = "True";
								- _Type = Bool;
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "CPP_CG";
				- Metaclasses = { IRPYRawContainer 
					- size = 6;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Attribute";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "Visibility";
								- _Value = "private";
								- _Type = Enum;
								- _ExtraTypeInfo = "private,protected,public,fromAttribute";
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Configuration";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "ShowCgSimplifiedModelPackage";
								- _Value = "False";
								- _Type = Bool;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Dependency";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "GenerateOriginComment";
								- _Value = "False";
								- _Type = Bool;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "File";
						- Properties = { IRPYRawContainer 
							- size = 4;
							- value = 
							{ IProperty 
								- _Name = "ImplementationFooter";
								- _Value = "
";
								- _Type = MultiLine;
							}
							{ IProperty 
								- _Name = "ImplementationHeader";
								- _Value = "//	Component		: $ComponentName 
//	Configuration 	: $ConfigurationName
//	Model Element	: $FullModelElementName
//!	File name		: $CM_Source$
//!	File version	: $CM_Revision$
//
//!	Date changed	: $CM_Date$
//!	Last change by	: $CM_Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, $CodeGeneratedYear. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.

";
								- _Type = MultiLine;
							}
							{ IProperty 
								- _Name = "SpecificationFooter";
								- _Value = "
";
								- _Type = MultiLine;
							}
							{ IProperty 
								- _Name = "SpecificationHeader";
								- _Value = "//	Component		: $ComponentName 
//	Configuration 	: $ConfigurationName
//	Model Element	: $FullModelElementName
//!	File name		: $CM_Source$
//!	File version	: $CM_Revision$
//
//!	Date changed	: $CM_Date$
//!	Last change by	: $CM_Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, $CodeGeneratedYear. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
";
								- _Type = MultiLine;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Framework";
						- Properties = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IProperty 
								- _Name = "EventIdType";
								- _Value = "Rhp_int16_t";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "HeaderFile";
								- _Value = "";
								- _Type = String;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Relation";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "DataMemberVisibility";
								- _Value = "Private";
								- _Type = Enum;
								- _ExtraTypeInfo = "Public, Protected, Private";
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "Dialog";
				- Metaclasses = { IRPYRawContainer 
					- size = 3;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Argument";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "CPP_CommonProperties";
								- _Value = "CPP_CG::Class::In,CPP_CG::Class::InOut,CPP_CG::Class::Out,CPP_CG::Type::In,CPP_CG::Type::InOut,CPP_CG::Type::Out";
								- _Type = String;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "AssociationEnd";
						- Properties = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IProperty 
								- _Name = "CPP_CommonProperties";
								- _Value = "CPP_CG::Relation::ImplementWithStaticArray,CPP_CG::Relation::Static";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "CommonProperties";
								- _Value = "CG::Relation::Ordered";
								- _Type = String;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Operation";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "CPP_CommonProperties";
								- _Value = "CPP_CG::Operation::ImplementationEpilog,CPP_CG::Operation::ImplementationProlog,CPP_CG::Operation::SpecificationEpilog,CPP_CG::Operation::SpecificationProlog,CPP_CG::Operation::ThrowExceptions,CPP_CG::Class::ReturnType,CPP_CG::Type::ReturnType";
								- _Type = String;
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "General";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Model";
						- Properties = { IRPYRawContainer 
							- size = 4;
							- value = 
							{ IProperty 
								- _Name = "ActiveCodeViewSensitivity";
								- _Value = "OnFocus";
								- _Type = Enum;
								- _ExtraTypeInfo = "ElementSelection,OnFocus";
							}
							{ IProperty 
								- _Name = "AdditionalLanguageKeywords";
								- _Value = "defined";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "DiagramIsSavedUnit";
								- _Value = "False";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "NamesRegExp";
								- _Value = "^(([a-zA-Z_][a-zA-Z0-9_]*)|(operator.+)|(/\\*.+)|(aomArg\\(.+)|(ommmswArg\\(.+))$";
								- _Type = String;
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "SequenceDiagram";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "General";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "AutoCreateExecutionOccurrence";
								- _Value = "True";
								- _Type = Bool;
							}
						}
					}
				}
			}
		}
	}
	- _name = "oxf";
	- Dependencies = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IDependency 
			- _id = GUID 0c95b6bc-11ab-4e6d-89f1-b3fda68bbd57;
			- _name = "MisraCpp";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "AppliedProfile";
					- _id = GUID d2eca2c1-e5a5-4296-9453-29283c4ed8bc;
				}
			}
			- _modifiedTimeWeak = 1.2.1990::0:0:0;
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IProfile";
				- _filename = "$OMROOT\\Settings\\MISRA\\MISRAC++.sbs";
				- _subsystem = "";
				- _class = "";
				- _name = "MISRAC++";
				- _id = GUID 5717d983-7bb5-4aba-bdc8-41bcb977f568;
			}
		}
	}
	- _modifiedTimeWeak = 3.1.2018::14:10:1;
	- _description = { IDescription 
		- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs17 See \\cf1\\ul\\protect Overview\\cf0\\lang1037\\ulnone\\protect0\\f1\\rtlch\\par
}";
		- Hyperlinks = { IRPYRawContainer 
			- size = 1;
			- value = 
			{ IInternalHyperlink 
				- _name = "Overview";
				- _textType = "NAME";
				- _target = { IHandle 
					- _m2Class = "IDiagram";
					- _id = GUID 9bf786cb-e353-407c-8701-a479d293d44b;
				}
			}
		}
	}
	- _lastID = 15;
	- _UserColors = { IRPYRawContainer 
		- size = 16;
		- value = 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 
	}
	- _defaultSubsystem = { ISubsystemHandle 
		- _m2Class = "ISubsystem";
		- _filename = "Design.sbs";
		- _subsystem = "";
		- _class = "";
		- _name = "Design";
		- _id = GUID 18ec95c6-2cfd-44f0-8b87-0bd933c303ce;
	}
	- _component = { IHandle 
		- _m2Class = "IComponent";
		- _filename = "oxfFiles.cmp";
		- _subsystem = "";
		- _class = "";
		- _name = "oxfFiles";
		- _id = GUID 33cc1e75-2467-437f-b33c-790b33b32e99;
	}
	- Multiplicities = { IRPYRawContainer 
		- size = 4;
		- value = 
		{ IMultiplicityItem 
			- _name = "1";
			- _count = 56;
		}
		{ IMultiplicityItem 
			- _name = "*";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "0,1";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "1..*";
			- _count = -1;
		}
	}
	- Subsystems = { IRPYRawContainer 
		- size = 5;
		- value = 
		{ ISubsystem 
			- fileName = "Analysis";
			- _id = GUID 7cad0227-fde7-46c2-b9fb-aec15ed90763;
		}
		{ ISubsystem 
			- fileName = "StandardTypes";
			- _id = GUID efa47fe8-228b-4838-88b9-0a2289fde640;
		}
		{ ISubsystem 
			- fileName = "Design";
			- _id = GUID 18ec95c6-2cfd-44f0-8b87-0bd933c303ce;
		}
		{ IProfile 
			- fileName = "CustomizableFramework";
			- _id = GUID 223c6964-9d24-455b-b15a-7852bc8d284e;
		}
		{ IProfile 
			- fileName = "MISRAC++";
			- _persistAs = "$OMROOT\\Settings\\MISRA";
			- _id = GUID 5717d983-7bb5-4aba-bdc8-41bcb977f568;
			- _partOfTheModelKind = referenceunit;
		}
	}
	- Diagrams = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IDiagram 
			- _id = GUID 9bf786cb-e353-407c-8701-a479d293d44b;
			- _myState = 8192;
			- _name = "Overview";
			- Annotations = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IComment 
					- _id = GUID cccfe528-73b2-4c6d-a0aa-600575274cf7;
					- _name = "ModelOverview";
					- _modifiedTimeWeak = 1.2.1990::0:0:0;
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fprq8\\fcharset0 Times New Roman;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\f0\\fs24 1. Purpose and current status of model\\par
This model describes the requirements analysis and design of the\\par
 Core Object eXecution Framework (COXF).\\par
2. The structure of the model\\par
The model has an Analysis package that \\par
specifies the requirements, use-cases, actors, analysis classes and analysis scenarios.\\par
The Design package specifies the architecture and \\par
  design scenarios derived from the Analysis package.\\par
3. How to browse the model?\\par
Analysis:\\par
- Start with the \\cf1\\ul\\protect FunctionalDomains diagram\\cf0\\ulnone\\protect0  under the Analysis package. \\par
Every package is traced to a set of high-level requirements (also directly under analysis).\\par
Each package has a main diagram that is a use case diagram and\\par
  can be opened using the Open Main Diagram command.\\par
- Each analysis package has a Use Case diagram called \\par
  \\ldblquote Requirements Vs. UseCases\\rdblquote  which details how the use cases are \\par
   traced to the requirements. \\par
Also, there is an Object Model Diagram called Actors which \\par
  details the actors involved in the package.\\par
- You can navigate from the use cases to their referenced sequence diagrams\\par
Design:\\par
- Start with the \\cf1\\ul\\protect Package overview OMD\\cf0\\ulnone\\protect0  and advance in the same technique as in the analysis.\\par
- The core behavioral framework interfaces and the \\par
  design level scenarios are located in the\\par
   CoreAPI package (in Design::oxf::Core).\\par
- The default implementation of the interfaces is located in the\\par
   CoreImplementation package (in Design::oxf::Core).\\lang1037\\f1\\rtlch\\par
}
";
						- Hyperlinks = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IInternalHyperlink 
								- _name = "FunctionalDomains diagram";
								- _textType = "FREE";
								- _target = { IHandle 
									- _m2Class = "IDiagram";
									- _filename = "Analysis.sbs";
									- _subsystem = "Analysis";
									- _class = "";
									- _name = "FunctionalDomains";
									- _id = GUID 8f1d14a1-fa30-4180-aba7-72e8956aa7c1;
								}
							}
							{ IInternalHyperlink 
								- _name = "Package overview OMD";
								- _textType = "FREE";
								- _target = { IHandle 
									- _m2Class = "IDiagram";
									- _filename = "Design.sbs";
									- _subsystem = "Design";
									- _class = "";
									- _name = "Packages overview";
									- _id = GUID ea033654-9b3d-4e59-b7e0-2fbea0425103;
								}
							}
						}
					}
					- _body = "";
				}
			}
			- _modifiedTimeWeak = 1.2.1990::0:0:0;
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Overview of the oxf model and how to review it\\f1\\rtlch\\par
}
";
			}
			- _lastID = 1;
			- _lastModifiedTime = "9.27.2005::8:28:33";
			- _graphicChart = { CGIClassChart 
				- _id = GUID ea0bdd55-2f2b-4cba-92c1-ce9d03f14fd0;
				- m_type = 0;
				- m_pModelObject = { IHandle 
					- _m2Class = "IDiagram";
					- _id = GUID 9bf786cb-e353-407c-8701-a479d293d44b;
				}
				- m_pParent = ;
				- m_name = { CGIText 
					- m_str = "";
					- m_style = "Arial" 10 0 0 0 1 ;
					- m_color = { IColor 
						- m_fgColor = 0;
						- m_bgColor = 0;
						- m_bgFlag = 0;
					}
					- m_position = 1 0 0  ;
					- m_nIdent = 0;
					- m_bImplicitSetRectPoints = 0;
					- m_nOrientationCtrlPt = 8;
				}
				- m_drawBehavior = 0;
				- m_bIsPreferencesInitialized = 0;
				- elementList = 3;
				{ CGICompositeClass 
					- _id = GUID 70eb38cc-ac89-427a-92ac-1f30a3afa06f;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IPropertySubject 
								- _Name = "Format";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 7;
											- value = 
											{ IProperty 
												- _Name = "Font.Font";
												- _Value = "Arial";
												- _Type = String;
											}
											{ IProperty 
												- _Name = "Font.FontColor";
												- _Value = "0,0,0";
												- _Type = Color;
											}
											{ IProperty 
												- _Name = "Font.Italic";
												- _Value = "0";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Font.Size";
												- _Value = "10";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Font.Weight";
												- _Value = "400";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Line.LineColor";
												- _Value = "255,255,255";
												- _Type = Color;
											}
											{ IProperty 
												- _Name = "Line.LineWidth";
												- _Value = "0";
												- _Type = Int;
											}
										}
									}
								}
							}
							{ IPropertySubject 
								- _Name = "General";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Graphics";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "FitBoxToItsTextuals";
												- _Value = "False";
												- _Type = Bool;
											}
										}
									}
								}
							}
						}
					}
					- m_type = 78;
					- m_pModelObject = { IHandle 
						- _m2Class = "IClass";
						- _filename = "Design.sbs";
						- _subsystem = "Design";
						- _class = "";
						- _name = "TopLevel";
						- _id = GUID 578fad8b-6f6c-4c52-95f8-8022a94edfd6;
					}
					- m_pParent = ;
					- m_name = { CGIText 
						- m_str = "TopLevel";
						- m_style = "Arial" 10 0 0 0 1 ;
						- m_color = { IColor 
							- m_fgColor = 0;
							- m_bgColor = 0;
							- m_bgFlag = 0;
						}
						- m_position = 1 0 0  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 0;
						- m_nOrientationCtrlPt = 5;
					}
					- m_drawBehavior = 0;
					- m_bIsPreferencesInitialized = 0;
					- m_AdditionalLabel = { CGIText 
						- m_str = "";
						- m_style = "Arial" 10 0 0 0 1 ;
						- m_color = { IColor 
							- m_fgColor = 0;
							- m_bgColor = 0;
							- m_bgFlag = 0;
						}
						- m_position = 1 0 0  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 0;
						- m_nOrientationCtrlPt = 1;
					}
					- m_polygon = 4 50 50  645 50  645 609  50 609  ;
					- m_nNameFormat = 0;
					- m_nIsNameFormat = 0;
					- Compartments = { IRPYRawContainer 
						- size = 0;
					}
				}
				{ CGIFreeText 
					- _id = GUID 1731241d-914d-43d2-95dd-29c227982545;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IPropertySubject 
								- _Name = "Format";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "FreeText";
										- Properties = { IRPYRawContainer 
											- size = 8;
											- value = 
											{ IProperty 
												- _Name = "Font.Font";
												- _Value = "Arial";
												- _Type = String;
											}
											{ IProperty 
												- _Name = "Font.FontColor";
												- _Value = "0,128,64";
												- _Type = Color;
											}
											{ IProperty 
												- _Name = "Font.Italic";
												- _Value = "0";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Font.Size";
												- _Value = "20";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Font.Weight";
												- _Value = "700";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Line.LineColor";
												- _Value = "0,128,64";
												- _Type = Color;
											}
											{ IProperty 
												- _Name = "Line.LineWidth";
												- _Value = "1";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Wordbreak";
												- _Value = "True";
												- _Type = Bool;
											}
										}
									}
								}
							}
							{ IPropertySubject 
								- _Name = "General";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Graphics";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "FitBoxToItsTextuals";
												- _Value = "False";
												- _Type = Bool;
											}
										}
									}
								}
							}
						}
					}
					- m_type = 46;
					- m_pModelObject = { IHandle 
						- _m2Class = "";
					}
					- m_pParent = GUID 867ab715-016e-403c-81eb-b63e33ffa123;
					- m_name = { CGIText 
						- m_str = "";
						- m_style = "Arial" 20 1 0 0 1 ;
						- m_color = { IColor 
							- m_fgColor = 32;
							- m_bgColor = 32;
							- m_bgFlag = 0;
						}
						- m_position = 4 13.0811662177103 9.88728215518402  28.558849298087 9.88728215518402  28.558849298087 13.0268228743182  13.0811662177103 13.0268228743182  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 1;
						- m_nOrientationCtrlPt = 8;
					}
					- m_drawBehavior = 4096;
					- m_transform = 0.126079 0 0 0.0939394 -27 27 ;
					- m_bIsPreferencesInitialized = 0;
					- m_points = 4 501 696  2587 696  2587 366  501 366  ;
					- m_text = "Model Overview

";
				}
				{ CGIAnnotation 
					- _id = GUID 867ab715-016e-403c-81eb-b63e33ffa123;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IPropertySubject 
								- _Name = "Format";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Comment";
										- Properties = { IRPYRawContainer 
											- size = 4;
											- value = 
											{ IProperty 
												- _Name = "Fill.FillColor";
												- _Value = "255,255,255";
												- _Type = Color;
											}
											{ IProperty 
												- _Name = "Font.Font";
												- _Value = "Times New Roman";
												- _Type = String;
											}
											{ IProperty 
												- _Name = "Font.Size";
												- _Value = "12";
												- _Type = Int;
											}
											{ IProperty 
												- _Name = "Line.LineColor";
												- _Value = "128,128,0";
												- _Type = Color;
											}
										}
									}
								}
							}
							{ IPropertySubject 
								- _Name = "General";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Graphics";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "FitBoxToItsTextuals";
												- _Value = "False";
												- _Type = Bool;
											}
										}
									}
								}
							}
						}
					}
					- m_type = 173;
					- m_pModelObject = { IHandle 
						- _m2Class = "IComment";
						- _id = GUID cccfe528-73b2-4c6d-a0aa-600575274cf7;
					}
					- m_pParent = GUID 70eb38cc-ac89-427a-92ac-1f30a3afa06f;
					- m_name = { CGIText 
						- m_str = "";
						- m_style = "Arial" 10 0 0 1 2 ;
						- m_color = { IColor 
							- m_fgColor = 0;
							- m_bgColor = 0;
							- m_bgFlag = 0;
						}
						- m_position = 1 23.2105263157895 3.83684210526315  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 0;
						- m_nOrientationCtrlPt = 8;
					}
					- m_drawBehavior = 4096;
					- m_transform = 0.630997 0 0 0.523807 65 99 ;
					- m_bIsPreferencesInitialized = 0;
					- m_polygon = 4 0 0  1084 0  1084 1096  0 1096  ;
					- m_nNameFormat = 0;
					- m_nIsNameFormat = 0;
					- Compartments = { IRPYRawContainer 
						- size = 0;
					}
					- _iTempdisplayTextFlag = 2;
					- m_bIsBoxStyle = 0;
				}
				
				- m_access = 'Z';
				- m_modified = 'N';
				- m_fileVersion = "";
				- m_nModifyDate = 0;
				- m_nCreateDate = 0;
				- m_creator = "";
				- m_bScaleWithZoom = 1;
				- m_arrowStyle = 'S';
				- m_pRoot = GUID 70eb38cc-ac89-427a-92ac-1f30a3afa06f;
				- m_currentLeftTop = 0 0 ;
				- m_currentRightBottom = 0 0 ;
				- m_bFreezeCompartmentContent = 0;
			}
			- _defaultSubsystem = { IHandle 
				- _m2Class = "ISubsystem";
				- _filename = "Design.sbs";
				- _subsystem = "";
				- _class = "";
				- _name = "Design";
				- _id = GUID 18ec95c6-2cfd-44f0-8b87-0bd933c303ce;
			}
		}
	}
	- Components = { IRPYRawContainer 
		- size = 3;
		- value = 
		{ IComponent 
			- fileName = "aom";
			- _id = GUID 3eecc3ce-a871-45a9-bdde-c891a69530d7;
		}
		{ IComponent 
			- fileName = "oxfAnimFiles";
			- _id = GUID 25cf3b15-286b-4eda-91a1-3f1788709d7e;
		}
		{ IComponent 
			- fileName = "oxfFiles";
			- _id = GUID 33cc1e75-2467-437f-b33c-790b33b32e99;
		}
	}
}

