I-Logix-RPY-Archive version 8.5.2 C++ 1146010
{ IClass 
	- _ownerHandle = { IHandle 
		- _m2Class = "ISubsystem";
		- _filename = "aom.sbs";
		- _subsystem = "Design";
		- _class = "";
		- _name = "aom";
		- _id = GUID bea74680-486c-4678-92f2-3f7ec624cc87;
	}
	- _id = GUID ae3b5a32-ffe4-4141-aeb4-552b9ffbbcae;
	- _myState = 8192;
	- _properties = { IPropertyContainer 
		- Subjects = { IRPYRawContainer 
			- size = 2;
			- value = 
			{ IPropertySubject 
				- _Name = "CG";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Class";
						- Properties = { IRPYRawContainer 
							- size = 3;
							- value = 
							{ IProperty 
								- _Name = "CreateImplicitDependencies";
								- _Value = "False";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "GenerateImplicitConstructors";
								- _Value = "False";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ImplicitDependencyToPackage";
								- _Value = "False";
								- _Type = Bool;
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "CPP_CG";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Framework";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "IncludeHeaderFile";
								- _Value = "False";
								- _Type = Bool;
							}
						}
					}
				}
			}
		}
	}
	- _name = "AnimServices";
	- Dependencies = { IRPYRawContainer 
		- size = 8;
		- value = 
		{ IDependency 
			- _id = GUID 3880a456-f4f0-43f4-8e50-2ffb0155584c;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "AOMInstance";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "aom.sbs";
				- _subsystem = "Design::aom";
				- _class = "";
				- _name = "AOMInstance";
				- _id = GUID e4f351f1-5f88-47c1-908a-70d19de4bc7f;
			}
		}
		{ IDependency 
			- _id = GUID 5bd9e997-2244-45cb-9d6a-08c00b2346ff;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "AOMSState";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "aom.sbs";
				- _subsystem = "Design::aom";
				- _class = "";
				- _name = "AOMSState";
				- _id = GUID 7e504786-4eec-44e4-9015-1aff771de605;
			}
		}
		{ IDependency 
			- _id = GUID 5760899b-2899-4cbc-9463-01f280d810fe;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfAnimTimerManager";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "AnimAPI.sbs";
				- _subsystem = "Design::oxf::Anim::AnimAPI";
				- _class = "";
				- _name = "IOxfAnimTimerManager";
				- _id = GUID 5f8f2a89-89d8-4e67-8427-8636a96c6f72;
			}
		}
		{ IDependency 
			- _id = GUID c6ee81c8-1669-4afb-be7e-a9f0d2c959e5;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfAnimReactive";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "AnimAPI.sbs";
				- _subsystem = "Design::oxf::Anim::AnimAPI";
				- _class = "";
				- _name = "IOxfAnimReactive";
				- _id = GUID 651b9f27-c545-4bd9-b337-04b02258d3cd;
			}
		}
		{ IDependency 
			- _id = GUID fb5bd1e9-e650-4f55-a75f-d7f44e0e0d03;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfEvent";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "CoreAPI.sbs";
				- _subsystem = "Design::oxf::Core::CoreAPI";
				- _class = "";
				- _name = "IOxfEvent";
				- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
			}
		}
		{ IDependency 
			- _id = GUID 0137d331-22e0-49b9-9e63-0c1b07946bda;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfReactive";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "CoreAPI.sbs";
				- _subsystem = "Design::oxf::Core::CoreAPI";
				- _class = "";
				- _name = "IOxfReactive";
				- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
			}
		}
		{ IDependency 
			- _id = GUID dbfd61b8-139b-4c69-ab00-a7f27b585466;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfTimeout";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "CoreAPI.sbs";
				- _subsystem = "Design::oxf::Core::CoreAPI";
				- _class = "";
				- _name = "IOxfTimeout";
				- _id = GUID 7ca39c06-5089-4ef7-8b23-98dead00f52d;
			}
		}
		{ IDependency 
			- _id = GUID 5d31d404-1726-4dd0-bfc3-c8298aad40f7;
			- _myState = 2048;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "CG";
						- Metaclasses = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Dependency";
								- Properties = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IProperty 
										- _Name = "UsageType";
										- _Value = "Existence";
										- _Type = Enum;
										- _ExtraTypeInfo = "Specification,Implementation,Existence";
									}
								}
							}
						}
					}
				}
			}
			- _name = "IOxfActive";
			- Stereotypes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IHandle 
					- _m2Class = "IStereotype";
					- _filename = "PredefinedTypes.sbs";
					- _subsystem = "PredefinedTypes";
					- _class = "";
					- _name = "Usage";
					- _id = GUID 42aa4325-6112-4e88-87ce-66008878f1db;
				}
			}
			- _dependsOn = { INObjectHandle 
				- _m2Class = "IClass";
				- _filename = "CoreAPI.sbs";
				- _subsystem = "Design::oxf::Core::CoreAPI";
				- _class = "";
				- _name = "IOxfActive";
				- _id = GUID 1485e2b9-f42a-4aad-a064-dd29adb2f339;
			}
		}
	}
	- Stereotypes = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IHandle 
			- _m2Class = "IStereotype";
			- _filename = "CustomizableFramework.sbs";
			- _subsystem = "CustomizableFramework";
			- _class = "";
			- _name = "utility";
			- _id = GUID 5be5d8fa-96ae-42d1-87c7-53b13f183a55;
		}
	}
	- _description = { IDescription 
		- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The AOM entry point for the OXF\\lang1037\\f1\\rtlch\\par
}
";
	}
	- _lastID = 31;
	- weakCGTime = 12.27.2008::8:57:24;
	- strongCGTime = 9.27.2005::7:39:12;
	- Operations = { IRPYRawContainer 
		- size = 52;
		- value = 
		{ IPrimitiveOperation 
			- _id = GUID 7159977f-32da-4b45-8d8c-53015c2aa451;
			- _name = "notifyEndApplication";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 notify the AOM that the application is about to terminate.\\par
The AOM should close the connection to Rhapsody.\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 247c570b-8c67-43ba-a0d1-7f2c913766a6;
					- _name = "closeConnection";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 When true the connection with Rhapsody is closed immediately, otherwise the close of the connection is postponed until the cleanup of the AOM\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypes.sbs";
						- _subsystem = "PredefinedTypes";
						- _class = "";
						- _name = "RhpBoolean";
						- _id = GUID f19b56f2-78ab-44fa-860e-6ead487ecb07;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID f47af5e7-f23a-4c79-a8d2-f975955bb5f8;
			- _name = "isApplicationEnding";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Query if the application is terminating, to be used by various AOM algorithms instead of query the OXF implementation\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 0;
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "bool";
				- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID efeea474-b1f5-4fdf-afe8-e9a96b09acdf;
			- _name = "registerAnimTimerManager";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Register the \\cf1\\ul\\protect IOxfAnimTimerManager\\cf0\\ulnone\\protect0  on the AOM to enable time control (stop timeouts in breakpoints, advance the time on \\b\\i go idle\\b0\\i0  commands, etc.)\\par
}
";
				- Hyperlinks = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IInternalHyperlink 
						- _name = "IOxfAnimTimerManager";
						- _textType = "NAME";
						- _target = { IHandle 
							- _m2Class = "IClass";
							- _filename = "AnimAPI.sbs";
							- _subsystem = "Design::oxf::Anim::AnimAPI";
							- _class = "";
							- _name = "IOxfAnimTimerManager";
							- _id = GUID 5f8f2a89-89d8-4e67-8427-8636a96c6f72;
						}
					}
				}
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID de64f4d7-94fa-4a2c-a3fd-d3470cbaac35;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "timerManager";
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "AnimAPI.sbs";
						- _subsystem = "Design::oxf::Anim::AnimAPI";
						- _class = "";
						- _name = "IOxfAnimTimerManager";
						- _id = GUID 5f8f2a89-89d8-4e67-8427-8636a96c6f72;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 81edc3b5-7c86-4466-a699-14ebf232c495;
			- _name = "notifyMutexLock";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Notify the animation that a thread is going through a mutex.\\par
The operation should be called twice, before and after the lock.\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID b87dd8fd-aeee-4dd3-a2e2-32a233ff3c64;
					- _name = "locked";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Indicates if the call was made before (false) or after (true) the lock\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypes.sbs";
						- _subsystem = "PredefinedTypes";
						- _class = "";
						- _name = "RhpBoolean";
						- _id = GUID f19b56f2-78ab-44fa-860e-6ead487ecb07;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 0581b6ca-bb6d-405e-beb2-cad41ba8b321;
			- _name = "notifyEventDestroyed";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Notify that an event is about to be destroyed\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID e7077907-faa7-46c9-8308-d2919c69cf62;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID c70d69fc-18d6-4bc7-b51b-2b074fdc183c;
			- _name = "notifyStartBehaviorBegin";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the behavior (i.e. statemachine) of a reactive instance is about to be activated.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID f312e2f7-a0c0-47af-afcc-0cc02e78523a;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 8e723d29-95dc-4d80-8b80-845ee69a9642;
			- _name = "notifyHandleEventBegin";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that an event is about to be handled\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 23ceb2a4-b458-4f9b-a026-0e69e9994af4;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID c0d81323-6da3-416d-b97a-8125c8875299;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 16c99674-778c-4f53-98e6-a7aeccbeb6f9;
			- _name = "notifyNullTransition";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a null-transition is about to be taken.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 1f78c41f-5ec2-4be8-94ed-33edf4c22c93;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID f3552029-84a6-4d84-9394-577cc5b87c05;
			- _name = "notifyStateEntered";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a state was entered\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID d91f5eb1-5343-456a-9422-7ca281490399;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state machine owner\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 537ad5e9-f250-4954-90ff-1d5e0f86dbe9;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "state";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state vector as string\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID fd0177f9-ac09-4351-b172-4271bad83f10;
			- _name = "notifyStateExited";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a state was exited\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 964019f1-f57c-47de-b8d2-ee24949492fb;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state machine owner\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 32c3c66c-6a52-4814-8886-1fa4fa9c02c1;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "state";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state vector as string\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 8b21b95b-df46-475f-a7a7-e75d8c67f363;
			- _name = "setThreadName";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Set the animation thread name\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID dc1deb34-5bf3-4507-a674-f9683b77f8e6;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 6e3b51d6-8510-41dc-a0b2-1412430bb58f;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "name";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The thread name\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 7ad45601-d1e0-4418-a0f9-02dd07066df0;
			- _name = "switchOSThread";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Switch the thread used by an implementation of \\cf1\\ul\\protect IOxfActive\\cf0\\ulnone\\protect0  (typically called by the default active class on the event loop initialization).\\par
}
";
				- Hyperlinks = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IInternalHyperlink 
						- _name = "IOxfActive";
						- _textType = "NAME";
						- _target = { IHandle 
							- _m2Class = "IClass";
							- _filename = "CoreAPI.sbs";
							- _subsystem = "Design::oxf::Core::CoreAPI";
							- _class = "";
							- _name = "IOxfActive";
							- _id = GUID 1485e2b9-f42a-4aad-a064-dd29adb2f339;
						}
					}
				}
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 430e3996-0463-4e27-8b0c-94e1da257138;
					- _name = "oldThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The old OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 7e16a1da-94a7-4f6c-85cd-2aa7f176b3c3;
					- _name = "newThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The new OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 583c080a-f6a2-415e-915e-1ff5dbe13501;
			- _name = "notifyTerminateConnector";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the reactive instance reached a terminate connector\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 3b34508e-0309-467d-bc63-f68cfe80a112;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID e74b10e7-fd6d-4e78-8176-d9ddbcb2141c;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "connector";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The terminate connector full name\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 47df9889-e4c4-4aa7-a68b-1c0154083f47;
			- _name = "notifyTimeoutCancelled";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a timeout was canceled\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 1d10b207-6d4a-476b-9c40-87cafe5b6878;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "tm";
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfTimeout";
						- _id = GUID 7ca39c06-5089-4ef7-8b23-98dead00f52d;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID ec11b23d-95f6-4724-a709-b99fe94046ba;
			- _name = "notifyTimeoutSet";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a timeout was scheduled\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID bda99322-55c9-4183-9d54-0adc2a0cbe3e;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "tm";
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfTimeout";
						- _id = GUID 7ca39c06-5089-4ef7-8b23-98dead00f52d;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 395185fc-679c-451f-bb18-2e592b82e3a6;
			- _name = "deregisterForeignThread";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 de-register an external thread (not related to active instances) that was registered on the animation\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID ff4ee503-a7b3-4feb-bef8-9daedfb15f29;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 9c739cca-7c6f-45d5-a8f8-7f605528f887;
			- _name = "registerForeignThread";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 register an external thread (not related to active instances) that was registered on the animation\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID a704bb88-2464-48d5-bfa7-cdccfab94002;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID ec8a3956-d6ae-48fa-b2b8-c240dcd0cc39;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "name";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The thread name\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID eddce761-f116-468d-b5c7-3d06e5803fcf;
			- _name = "notifyError";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Nofiy the animation that an error occured\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID b67eb330-2b33-43d3-823b-df8a21a3bae3;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "msg";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The error message\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 70a7feed-726d-4d50-b288-3836afae075b;
			- _name = "notifyError";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Nofiy the animation that an error occured\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID a54bfb81-73c3-44ed-9322-024757f6661c;
					- _name = "context";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The contect (instance) that the error was found in\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 5b5b197f-222d-4812-ad8d-bb5fc121a03e;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "msg";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The error message\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID cbad557d-89de-45ea-bb85-2e89962fbef9;
			- _name = "notifySendingEvent";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that an event is being send\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID e19c4fcc-1cca-4376-a72f-02d572b86e62;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 2f56e62d-b002-495f-89fb-efda197e35af;
					- _name = "params";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event sending parameters\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEventGenerationParams";
						- _id = GUID 4aeea12e-4ea6-45bc-8ba2-b8498ce3a0a7;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID ae500f58-92cc-47fb-8bc7-d95bf9a55b63;
			- _name = "notifyThreadCreated";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a thread was created\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID be8703fa-2cf9-4510-8e74-da49d5553dfb;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "context";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The active class\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfActive";
						- _id = GUID 1485e2b9-f42a-4aad-a064-dd29adb2f339;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 30c5221d-7d78-4b87-a569-8540384ae127;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID ddcff3de-70ca-49dc-ae0a-e25f8777deea;
			- _name = "notifyThreadDestroyed";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a thread is about to be destroyed\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 20a73978-5807-4770-8f07-34310d69c510;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID ae5b2394-1aa6-45df-8dd2-1fa023311c32;
			- _name = "notifyEventCancelled";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that an event was canceled (required for direct reactive deletion)\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID c2d1b4c2-4b82-41c2-a8c6-e7b267e1b90e;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread identifier\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID c006d87b-f609-4851-a451-a2c46965fcf6;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID f7f30f4c-9a3d-4977-86fc-450bdea8fde6;
			- _name = "resetCallStack";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Reset the call stack associated with the specified thread\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 38ae5d5a-da56-48a3-95c3-713becaf8a94;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 7cb44cab-cf1f-4d6f-b249-ca965e872337;
			- _name = "notifyIdle";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the specified thread is idle (no events to consume)\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 8453b3f0-28dc-45b6-88e4-42965eadf317;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID a43cfb03-cd4a-458b-8af5-7902b606d005;
			- _name = "notifyReady";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the specified thread is ready to run.\\par
This is used by the animation to perform function calls on the context of the thread before continue the event loop.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 9ef60754-584f-45ae-9753-a136f2542abe;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID c5376200-345d-4c5b-8363-cf45c1938476;
			- _name = "notifyFirstStep";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the first step was performed (e.g. OXF::initialize()) in the context of the specified thread.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID df89a13d-a031-479b-9609-c18c2920675c;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 75c60182-ad6f-4e6a-ab7c-a3becdf2a949;
			- _name = "init";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Initialize the animation\\par
Return true if the initialization was sucessful\\par
Animated applications should terminate if the return value is false.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 4;
				- value = 
				{ IArgument 
					- _id = GUID 27f57622-9fd5-4749-b9f4-0c17af3662fa;
					- _name = "argc";
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "MISRA_Cpp_Types.sbs";
						- _subsystem = "Design::oxf::Services::Types::MISRA_Cpp_Types";
						- _class = "";
						- _name = "Rhp_int32_t";
						- _id = GUID 55012af4-7758-4935-bf1e-dc3777a3b025;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 86fb61b2-97a2-41e4-9de7-74dfc2b2bbb9;
					- _name = "argv";
					- myTypeOf = { IType 
						- _id = GUID 36171ff9-35c1-4ebd-9054-63dbe8a9d479;
						- _myState = 8192;
						- _declaration = "char**";
						- _kind = Language;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 68bb1241-83bb-4533-bc87-23f254f4cb8b;
					- _name = "defaultPort";
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "MISRA_Cpp_Types.sbs";
						- _subsystem = "Design::oxf::Services::Types::MISRA_Cpp_Types";
						- _class = "";
						- _name = "Rhp_uint32_t";
						- _id = GUID 0c2ec2f1-71b8-421f-a5a4-3d7dbe1aba28;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 9dde53c0-49e3-4125-b8a7-c5d2bd83cae6;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "defaultHost";
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "bool";
				- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 32a9c86f-1ebe-44c4-a2d4-f52292f1a1e6;
			- _name = "notifyEventGetBegin";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the specified thread is about remove an event from the queue\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID d96499f7-071e-4ec4-bc1e-c51d6d61a071;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID b8620695-ce17-4b00-8502-74215760b67a;
					- _name = "add2q";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Indicates that the event is part of the animation reflection queue\\lang1037\\f1\\rtlch\\par
}
";
					}
					- ValueSpecifications = { IRPYRawContainer 
						- size = 1;
						- value = 
						{ ILiteralSpecification 
							- _id = GUID 8311917f-dfed-4705-87d6-e1257e1b6e66;
							- _value = "true";
						}
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID f0eef304-cd39-42c7-8a79-f55966c115ec;
			- _name = "notifyFrameworkStarted";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify the AOM that the framework default message loop isactivated\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 0;
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
			- _itsBody = { IBody 
				- _bodyData = "// force sending last constructor notification
OMGetCurrentCallStack()->notify(
	reinterpret_cast<AOMAnimationItem*>(1), omConstructorMethod);
";
			}
		}
		{ IPrimitiveOperation 
			- _id = GUID 87ae6670-149b-4392-88ed-80699eff593a;
			- _name = "getAnimInstance";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Return the animation instance that is associated with the specified \"real\" instance\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID cb5b211b-33f6-4279-bffa-65f8d9b1a44c;
					- _name = "inst";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The real instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IClass";
				- _filename = "aom.sbs";
				- _subsystem = "Design::aom";
				- _class = "";
				- _name = "AOMInstance";
				- _id = GUID e4f351f1-5f88-47c1-908a-70d19de4bc7f;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID a123e73f-a823-4254-988a-98942a095cab;
			- _name = "addState";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Add the state information to the AOM state vector\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 4d955b17-12fe-4406-8663-798f757806b0;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "InOut";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "states";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The AOM states vector\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "aom.sbs";
						- _subsystem = "Design::aom";
						- _class = "";
						- _name = "AOMSState";
						- _id = GUID 7e504786-4eec-44e4-9015-1aff771de605;
					}
					- _isOrdered = 0;
					- _argumentDirection = InOut;
				}
				{ IArgument 
					- _id = GUID a235c086-5952-4fd4-a6bc-ef83c3790f08;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "state";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state name\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 4dd66a6b-1e2b-4a20-a7a1-1e6dda7647d3;
			- _name = "addTerminateState";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Add the state information to the AOM state vector\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID f0f45ad8-cad5-49f8-a943-5a88ac54a003;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "InOut";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "states";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The AOM states vector\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "aom.sbs";
						- _subsystem = "Design::aom";
						- _class = "";
						- _name = "AOMSState";
						- _id = GUID 7e504786-4eec-44e4-9015-1aff771de605;
					}
					- _isOrdered = 0;
					- _argumentDirection = InOut;
				}
				{ IArgument 
					- _id = GUID e98913de-f5c2-4bad-b30f-399e84aaf85b;
					- _name = "shouldTerminate";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 true when a terminte should be added\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 833bb419-4b9d-4e1e-bc98-c9a10d024d03;
			- _name = "notifyStateEntered";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a state was entered\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 7d762cf7-b05d-467e-85d3-3c7beb415554;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state machine owner\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "aom.sbs";
						- _subsystem = "Design::aom";
						- _class = "";
						- _name = "AOMInstance";
						- _id = GUID e4f351f1-5f88-47c1-908a-70d19de4bc7f;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 16682c85-3239-4484-af51-406031fd422b;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "state";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state vector as string\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 99aa99c2-9fcd-46f8-8d5f-4290a098cce6;
			- _name = "notifyStateExited";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a state was exited\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID d5465d13-08b9-42ba-9579-a74d0be9e238;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state machine owner\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "aom.sbs";
						- _subsystem = "Design::aom";
						- _class = "";
						- _name = "AOMInstance";
						- _id = GUID e4f351f1-5f88-47c1-908a-70d19de4bc7f;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID d27896aa-fc32-480e-905e-35acc38cb641;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Type";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "state";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The state vector as string\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "char*";
						- _id = GUID a1f818e6-c022-42d5-bbc0-075bf073b055;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 48988ece-6406-46d8-9591-514daeaae100;
			- _name = "shouldNotifyIdle";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}}
{\\colortbl ;\\red0\\green0\\blue255;\\red0\\green0\\blue0;}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Check if the specified thread should become idle.\\par
If this operation returns true \\cf1\\ul\\protect notifyIdle()\\cf0\\ulnone\\protect0  should be called otherwise you should wait for events and then call \\cf1\\ul\\protect notifyReady()\\cf2\\ulnone\\protect0\\par
}
";
				- Hyperlinks = { IRPYRawContainer 
					- size = 2;
					- value = 
					{ IInternalHyperlink 
						- _name = "notifyIdle()";
						- _textType = "FREE";
						- _target = { IHandle 
							- _m2Class = "IPrimitiveOperation";
							- _id = GUID 7cb44cab-cf1f-4d6f-b249-ca965e872337;
						}
					}
					{ IInternalHyperlink 
						- _name = "notifyReady()";
						- _textType = "FREE";
						- _target = { IHandle 
							- _m2Class = "IPrimitiveOperation";
							- _id = GUID a43cfb03-cd4a-458b-8af5-7902b606d005;
						}
					}
				}
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 1bd7cfd9-85d5-4a58-b889-4153167dd011;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "bool";
				- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 8b481674-1f38-4172-ae2c-eccb87fff5da;
			- _name = "registerReactiveInstance";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Register a reactive instance with its animation proxy\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 1b95a775-dd35-49d7-af2b-27fc602de775;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 4de5ca97-3bb8-4862-ba04-a97e256abf80;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "proxy";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The animation proxy\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "AnimAPI.sbs";
						- _subsystem = "Design::oxf::Anim::AnimAPI";
						- _class = "";
						- _name = "IOxfAnimReactive";
						- _id = GUID 651b9f27-c545-4bd9-b337-04b02258d3cd;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID dab1d074-10e1-4395-9306-cd033fc38780;
			- _name = "notifyEventPutEnd";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the event was put into the thread queue\\par
\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 3;
				- value = 
				{ IArgument 
					- _id = GUID d664b42f-f98b-4e56-a64f-7a84d1ec5715;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 39c6876a-d89a-4721-aca3-82e0ca030c54;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 24e5427a-8f37-47cb-816e-edbffc61aeca;
					- _name = "add2q";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Indicates that the event is part of the animation reflection queue\\lang1037\\f1\\rtlch\\par
}
";
					}
					- ValueSpecifications = { IRPYRawContainer 
						- size = 1;
						- value = 
						{ ILiteralSpecification 
							- _id = GUID 7c2d4e6a-d187-405a-a349-0ab5404740f2;
							- _value = "true";
						}
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 9718a584-ea3c-43ec-a558-dd670ad61eb7;
			- _name = "notifyEventPutBegin";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the event is about to be put into the thread queue\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 4;
				- value = 
				{ IArgument 
					- _id = GUID 8c266ba3-7381-4412-b1a8-9478a7e92e2c;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 3cac3faa-4330-4862-a62e-d42fe6794bd9;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID e2d03179-bf4c-49a8-bc3a-a2b6654aaf49;
					- _name = "blocking";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 If the put of the event queue is expected to be a blocking call for a significant time duration this is indicated by setting this argument to true\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID fe08c345-cf7a-4077-9cdd-ac0acc2149e7;
					- _name = "add2q";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Indicates that the event is part of the animation reflection queue\\lang1037\\f1\\rtlch\\par
}
";
					}
					- ValueSpecifications = { IRPYRawContainer 
						- size = 1;
						- value = 
						{ ILiteralSpecification 
							- _id = GUID 219d27f4-0780-4180-8cc6-ad12e7aa1e27;
							- _value = "true";
						}
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 00142a31-8ffb-4f46-b580-f0289b02f1f8;
			- _name = "notifyEventGetEnd";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the specified thread removed the event from the queue\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 3;
				- value = 
				{ IArgument 
					- _id = GUID 07c3aa2b-7cfd-4b7a-8c59-f389e7b8c021;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread handle, when 0 the animation assumes that the context is the current thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID c07e2920-58a4-400e-bcbd-3fc0efa0ac58;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event that was removed\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 12361110-6ca5-46e7-81db-5f2bb0d81535;
					- _name = "add2q";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Indicates that the event is part of the animation reflection queue\\lang1037\\f1\\rtlch\\par
}
";
					}
					- ValueSpecifications = { IRPYRawContainer 
						- size = 1;
						- value = 
						{ ILiteralSpecification 
							- _id = GUID ea3d1491-00ac-4b27-b2c1-dc63ccd8940c;
							- _value = "true";
						}
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "bool";
						- _id = GUID e6c263cc-4bc5-4a11-b32d-02148c93add0;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 5b3925b3-7ba3-47a9-839a-e7aa75165e0c;
			- _name = "notifyHandleEventEnd";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that an event was handled\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 58423092-ae16-4f18-a901-ef068eb4d3e2;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 6abb8b47-507e-483d-9120-6a7f39ce017e;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID bcddca63-56d6-4250-87eb-eb91144c9edf;
			- _name = "notifyStartBehaviorEnd";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that the behavior (i.e. statemachine) of a reactive instance is completed.\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID fbd31fb8-521f-4544-95ac-0729e01eba6a;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 4649092d-2aac-439a-b77c-c97ba3100212;
			- _name = "notifyFrameworkEventCreated";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that a framework animated event was created\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID a635bed5-b8a7-4949-9fe8-9ad46a926fad;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "ev";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The event\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfEvent";
						- _id = GUID 72bafe6b-3c6c-4462-88b7-148dc2ae21b9;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 98b31620-62da-481d-9eea-a1b699c198d7;
			- _name = "registerAnimThreadManager";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Register the threads manager\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 2eb60168-9bac-40f6-9a9d-0ae9008a29ff;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "manager";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The threads manager\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "AnimAPI.sbs";
						- _subsystem = "Design::oxf::Anim::AnimAPI";
						- _class = "";
						- _name = "IOxfAnimThreadManager";
						- _id = GUID fadd4b9d-7916-4fb6-b18a-2bfd8cb2318b;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 6764fe37-646a-4b9c-8864-e66c68e97196;
			- _name = "getThreadManager";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Return the threads manager\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 0;
			}
			- _returnType = { IHandle 
				- _m2Class = "IClass";
				- _filename = "AnimAPI.sbs";
				- _subsystem = "Design::oxf::Anim::AnimAPI";
				- _class = "";
				- _name = "IOxfAnimThreadManager";
				- _id = GUID fadd4b9d-7916-4fb6-b18a-2bfd8cb2318b;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID e37219cc-072f-468a-9996-cff28b03aa86;
			- _name = "getTimerManager";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Return the timer manager\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 0;
			}
			- _returnType = { IHandle 
				- _m2Class = "IClass";
				- _filename = "AnimAPI.sbs";
				- _subsystem = "Design::oxf::Anim::AnimAPI";
				- _class = "";
				- _name = "IOxfAnimTimerManager";
				- _id = GUID 5f8f2a89-89d8-4e67-8427-8636a96c6f72;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID d14f18f4-29fb-40fd-96a3-d40592002285;
			- _name = "notifyEventStep";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Notify that an event step had occured\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID e4f1f10c-ca0f-4590-8b7a-f7b1b965b645;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The OS thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 5ccd4ed2-5054-445a-841c-c94962447b89;
			- _name = "setThreadContext";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Set the animation thread name by an animation instance\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID 4e9edc9a-5dcd-4b31-927f-2c08184a623f;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "oxfContext";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The active context\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfActive";
						- _id = GUID 1485e2b9-f42a-4aad-a064-dd29adb2f339;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 734248d9-f3d4-4005-b867-04b5f21d16b8;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 The instance to set as the thread context\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "aom.sbs";
						- _subsystem = "Design::aom";
						- _class = "";
						- _name = "AOMInstance";
						- _id = GUID e4f351f1-5f88-47c1-908a-70d19de4bc7f;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 16cfbc76-285b-4bc3-8394-d95cc8436b6b;
			- _name = "registerAnimHelper";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 register the singleton implementation of \\cf1\\ul\\protect IOxfAnimHelper\\cf0\\ulnone\\protect0\\par
}
";
				- Hyperlinks = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IInternalHyperlink 
						- _name = "IOxfAnimHelper";
						- _textType = "NAME";
						- _target = { IHandle 
							- _m2Class = "IClass";
							- _filename = "AnimAPI.sbs";
							- _subsystem = "Design::oxf::Anim::AnimAPI";
							- _class = "";
							- _name = "IOxfAnimHelper";
							- _id = GUID 89d3da57-4f62-46f0-9685-0c90b83f9ffa;
						}
					}
				}
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID c205c8ac-a3cc-410a-b70b-cf4f97b20727;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "animHelper";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
{\\colortbl ;\\red0\\green0\\blue255;}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 the \\cf1\\ul\\protect IOxfAnimHelper\\cf0\\ulnone\\protect0  singleton implementation\\lang1037\\f1\\rtlch\\par
}
";
						- Hyperlinks = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IInternalHyperlink 
								- _name = "IOxfAnimHelper";
								- _textType = "NAME";
								- _target = { IHandle 
									- _m2Class = "IClass";
									- _filename = "AnimAPI.sbs";
									- _subsystem = "Design::oxf::Anim::AnimAPI";
									- _class = "";
									- _name = "IOxfAnimHelper";
									- _id = GUID 89d3da57-4f62-46f0-9685-0c90b83f9ffa;
								}
							}
						}
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "AnimAPI.sbs";
						- _subsystem = "Design::oxf::Anim::AnimAPI";
						- _class = "";
						- _name = "IOxfAnimHelper";
						- _id = GUID 89d3da57-4f62-46f0-9685-0c90b83f9ffa;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID ef97aaaa-68a9-4787-a459-3da98b7ad846;
			- _name = "notifyReactiveInstanceDeleted";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 Notify that a reactive instance is deleted\\lang1037\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IArgument 
					- _id = GUID 3380d191-1d2c-4474-9990-18475f708abc;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "const $type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "instance";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 The reactive instance\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfReactive";
						- _id = GUID 987d60d7-a9be-4b5d-b578-e27190b2c836;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID c83a9fee-c0a5-492d-8404-6d8d5424a632;
			- _name = "cleanupOnEndApplication";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Perform explicit AOM cleanup\\par
Required to cleanup the AOM in adapters that do not support automatic cleanup\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 0;
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
		{ IPrimitiveOperation 
			- _id = GUID 2acb9843-c8ea-4bb6-849d-8ac132f0a5e9;
			- _name = "resetDefaultThread";
			- _description = { IDescription 
				- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\fs20 Reset the default thread RTOS identifier\\f1\\rtlch\\par
}
";
			}
			- _virtual = 0;
			- Args = { IRPYRawContainer 
				- size = 2;
				- value = 
				{ IArgument 
					- _id = GUID cf7702d7-5e19-4e5a-b9db-feb0b5067dde;
					- _properties = { IPropertyContainer 
						- Subjects = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IPropertySubject 
								- _Name = "CPP_CG";
								- Metaclasses = { IRPYRawContainer 
									- size = 1;
									- value = 
									{ IPropertyMetaclass 
										- _Name = "Class";
										- Properties = { IRPYRawContainer 
											- size = 1;
											- value = 
											{ IProperty 
												- _Name = "In";
												- _Value = "$type*";
												- _Type = String;
											}
										}
									}
								}
							}
						}
					}
					- _name = "oxfContext";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 the active context\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IClass";
						- _filename = "CoreAPI.sbs";
						- _subsystem = "Design::oxf::Core::CoreAPI";
						- _class = "";
						- _name = "IOxfActive";
						- _id = GUID 1485e2b9-f42a-4aad-a064-dd29adb2f339;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
				{ IArgument 
					- _id = GUID 8051ad11-e05f-4403-89c1-49ae88f35049;
					- _name = "osThread";
					- _description = { IDescription 
						- _textRTF = "{\\rtf1\\fbidis\\ansi\\ansicpg1255\\deff0\\deflang1037{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}{\\f1\\fnil\\fcharset177{\\*\\fname Arial;}Arial (Hebrew);}}
\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\fs20 the new OS identifier of the main thread\\lang1037\\f1\\rtlch\\par
}
";
					}
					- _typeOf = { IHandle 
						- _m2Class = "IType";
						- _filename = "PredefinedTypesC++.sbs";
						- _subsystem = "PredefinedTypesCpp";
						- _class = "";
						- _name = "void *";
						- _id = GUID 68975846-a809-4f2e-9f11-00ad6073974c;
					}
					- _isOrdered = 0;
					- _argumentDirection = In;
				}
			}
			- _returnType = { IHandle 
				- _m2Class = "IType";
				- _filename = "PredefinedTypesC++.sbs";
				- _subsystem = "PredefinedTypesCpp";
				- _class = "";
				- _name = "void";
				- _id = GUID c6b70728-b655-45a0-abb7-8ea5d3da94be;
			}
			- _abstract = 0;
			- _final = 0;
			- _concurrency = Sequential;
			- _protection = iPublic;
			- _static = 1;
			- _constant = 0;
		}
	}
	- _multiplicity = "";
	- _itsStateChart = { IHandle 
		- _m2Class = "";
	}
	- _classModifier = Unspecified;
}

