int InsertSorted(Position head, Position nE) {
	*Position temo = head;

	*while (temp->next && temp->next->exp < nE->exp) {
		*temp = temp->next;
		*
	}
	*
		*if (temp->next == NULL || temp->next->exp != nE->exp)
		* {
		*InsertAfter(temp, nE);
		*
	}
		else {
		int resultCoeffient = temp->next->coeff + nE->coeff;

		if (resultCoeffient == 0)
		{
			DeliteAfter(temp);
			free(nE);
		}
		else {
			temp->next->coeff = resultCoeff;
			free(nE);
		}

		//citanje iz datoteke

		fgets(buffer, MAX_LINE, file); //buffer string koji nam ne treba, nama treba element po element pa koristimo sscanf jer ona ide dva po dva broja koja nama trebaju jer jejedan eksp a jedan koef 
		while (strlen(buffer) > 0) {
			int status = sscanf(buffer, " %d %d %n", &c, &e, &numBytes); //%n cita koliko je sscanf procitao bajtova//space izmedu " i %d da popuni prazninu tj poslije svaka dva broja prazno pretp da ih odvoji 
			.//ako nama sscanf vrati 2 uspijesno smo procitali i zelimo ih poslati u funkciju 
				.NAPRAVIT LOGIKU LOGICNO
				.
				buffer = buffer + numBytes;
		}
