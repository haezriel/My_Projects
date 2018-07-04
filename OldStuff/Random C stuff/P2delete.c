while (list->next != NULL){
	prev=list;
	list=list->next;
	if (list->data==num){
	prev->next=list->next;
	free(list);

	return;
	}
}
printf("Node not found.\n");
