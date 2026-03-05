#### Definitions porject specific definitions ####

set(project_prog_type_defines
	${project_prog_type_defines_project_specific}
	PROJECT_PROG_TYPE_STRING="${PROJECT_PROG_TYPE}"
	PROG_TYPE_${PROJECT_PROG_TYPE}			# e.g. PROG_TYPE_FSBL or PROG_TYPE_APPLI 
)