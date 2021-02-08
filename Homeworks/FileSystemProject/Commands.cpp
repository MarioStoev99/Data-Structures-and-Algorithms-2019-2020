#include "Commands.h"

void Commands::ls() {
	vector<bool> lsRights(2,false);
	lsRights[0] = true;
	lsRights[1] = true;
	pair <string, vector<bool >> lsCommand("ls", lsRights);
	commands.push_back(lsCommand);
}
void Commands::mkdir() {
	vector<bool> mkdirRights(2,false);
	mkdirRights[1] = true;
	pair <string, vector<bool >> mkdirCommand("mkdir", mkdirRights);
	commands.push_back(mkdirCommand);
}
void Commands::rmdir() {
	vector<bool> rmdirRights(2,false);
	rmdirRights[1] = true;
	pair <string, vector<bool >> rmdirCommand("rmdir", rmdirRights);
	commands.push_back(rmdirCommand);
}
void Commands::cd() {
	vector<bool> cdRights(2,false);
	cdRights[1] = true;
	pair <string, vector<bool >> cdCommand("cd", cdRights);
	commands.push_back(cdCommand);
}
void Commands::cp() {
	vector<bool> cpRights(3, false);
	cpRights[2] = true;
	pair <string, vector<bool >> cpCommand("cp", cpRights);
	commands.push_back(cpCommand);
}
void Commands::rm() {
	vector<bool> rmRights(2, false);
	rmRights[1] = true;
	pair <string, vector<bool >> rmCommand("rm", rmRights);
	commands.push_back(rmCommand);
}
void Commands::cat() {
	vector<bool> catRights(2, false);
	catRights[1] = true;
	pair <string, vector<bool >> catCommand("cat", catRights);
	commands.push_back(catCommand);
}
void Commands::write() {
	vector<bool> writeRights(3, false);
	writeRights[1] = true;
	writeRights[2] = true;
	pair <string, vector<bool >> writeCommand("write", writeRights);
	commands.push_back(writeCommand);
}
void Commands::import() {
	vector<bool> importRights(4, false);
	importRights[2] = true;
	importRights[3] = true;
	pair <string, vector<bool >> importCommand("import", importRights);
	commands.push_back(importCommand);
}
void Commands::exportCommand() {
	vector<bool> exportRights(3, false);
	exportRights[2] = true;
	pair <string, vector<bool >> exportCommand("export", exportRights);
	commands.push_back(exportCommand);
}
void Commands::exit() {
	vector<bool> exitRights(1, false);
	exitRights[0] = true;
	pair<string, vector<bool>> exitCommand("exit", exitRights);
	commands.push_back(exitCommand);
}
Commands::Commands() {
	ls();
	mkdir();
	rmdir();
	cd();
	cp();
	rm();
	cat();
	write();
	import();
	exportCommand();
	exit();
}
int Commands::findCommandIndex(const string& userCommand) const {
	for (int i = 0; i < commands.size(); ++i) {
		if (commands[i].first == userCommand) {
			return i;
		}
	}
	return -1;
}
bool Commands::hasValidArguments(int index,int argument) const {
	if (argument >= commands[index].second.size()) {
		throw InvalidArgumentsOfCommand();
	}
	return commands[index].second[argument] == true;
}