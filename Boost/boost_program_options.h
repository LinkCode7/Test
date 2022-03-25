#pragma once


/*
·ÖÎöÆ÷
parse_command_line¡¢parse_config_file¡¢parse_environment(ÄÚ²¿command_line_parser)
*/


int po_commandline(int argc, char*argv[]);

int po_commandline_options_description(int argc, char*argv[]);

void po_config_file();
