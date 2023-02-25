#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "deck.h"

/**
 * swap_next - swaps node with next node
 *
 * @deck: address of pointer to head
 * @node: node to swap
 */

void swap_next(deck_node_t **deck, deck_node_t *node)
{
	node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	else
		*deck = node->next;
	node->prev = node->next;
	node->next = node->next->next;
	node->prev->next = node;
	if (node->next)
		node->next->prev = node;
}

/**
 * deck_len - returns the length of a card deck
 *
 * @h: head node to the deck
 *
 * Return: the size of the deck
 */

size_t deck_len(const deck_node_t *h)
{
	size_t cnt = 0;

	while (h != NULL)
	{
		cnt++;
		h = h->next;
	}

	return (cnt);
}

/**
 * card_to_int - assigns a unique numeric value to each card
 *
 * @node: the card node to extract the value from
 *
 * Return: a unique card id
 */

int card_to_int(deck_node_t *node)
{
	int i;
	char *values[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9",
			"10", "Jack", "Queen", "King"};

	for (i = 0; i < 13; i++)
	{
		if (!strcmp(node->card->value, values[i]))
			return (i + (13 * node->card->kind));
	}

	printf("Uh-oh. Card is out of range. I'm gonna crash now.");
	exit(EXIT_FAILURE);
}

/**
 * sort_deck - sorts the deck with cocktail shaker
 *
 * @deck: the card deck to sort
 */

void sort_deck(deck_node_t **deck)
{
	int swapped = 1, val1, val2;
	size_t lo = 0, hi = (deck_len(*deck) - 1), i = 0;
	deck_node_t *tmp = *deck;

	if (!deck || !(*deck) || !((*deck)->next))
		return;
	while (swapped)
	{
		swapped = 0;
		for (; i < hi; i++)
		{
			val1 = card_to_int(tmp);
			val2 = card_to_int(tmp->next);
			if (val2 < val1)
			{
				swap_next(deck, tmp);
				swapped = 1;
			}
			else
				tmp = tmp->next;
		}
		if (!swapped)
			break;
		swapped = 0;
		for (; i > lo; i--)
		{
			val1 = card_to_int(tmp);
			val2 = card_to_int(tmp->prev);
			if (val2 > val1)
			{
				swap_next(deck, tmp->prev);
				swapped = 1;
			}
			else
				tmp = tmp->prev;
		}
		hi -= 1;
		lo += 1;
	}
}
