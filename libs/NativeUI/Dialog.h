/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file Dialog.h
 * @author emma
 *
 * \brief Class that represents a modal dialog.
 * A dialog cannot have any parent, it acts only as a container of other widgets.
 * A dialog is a sort of modal view, that can look different depending on
 * the platform:
 *  - On Android it is a modal alert dialog.
 *  - On iPad it is a PopoverController, and on iPhone it is a view.
 *
 * When a Dialog widget is created it is empty, it has no content.
 * Use setMainWidget(widget) to set the main widget of the dialog.
 * Besides the containing widgets, the Dialog can have two buttons on Android:
 *  - one left button that points to a Ready state.
 *  - one right button that points to a Cancel state.
 *  Those buttons are visible on the bottom of the dialog.
 *
 * A Dialog gets visible only after calling show() method.
 * To show a Dialog call show(), to hide it call: hide().
 */

#ifndef NATIVEUI_DIALOG_H_
#define NATIVEUI_DIALOG_H_

#include "Widget.h"

namespace NativeUI
{

	class DialogListener;

	/**
	 * \brief Class that represents a modal dialog.
	 */
	class Dialog : public Widget
	{
	public:
		/**
		 * Constructor.
		 */
		Dialog();

		/**
		 * Destructor.
		 */
		virtual ~Dialog();

		/**
		 * Set the title of the dialog.
		 * If the title is an empty string, the title bar becomes invisible.
		 * @param title The dialog title.
		 */
		virtual void setTitle(const MAUtil::String& title);

		/**
		 * Sets the text for the left side button.
		 * Note: it is available on Android only.
		 * This button is located at the bottom and it indicates a positive
		 * action, like Done/OK.
		 * The dialog gets hidden after this button is clicked.
		 * If the property receives am empty string then the button becomes
		 * invisible.
		 */
		virtual void setLeftButtonTitle(const MAUtil::String& title);

		/**
		 * Sets the text for the right side button.
		 * Note: it is available on Android only.
		 * This button is located at the bottom and it indicates a cancel
		 * action.
		 * The dialog gets hidden after this button is clicked.
		 * If the property receives am empty string then the button becomes
		 * invisible.
		 */
		virtual void setRightButtonTitle(const MAUtil::String& title);

		/**
		 * Set the main widget of the dialog.
		 * Note: A dialog can only have one main widget.
		 * Use a layout as main widget and add child  widgets to the layout.
		 * @param widget The widget to be set as main widget.
		 * The ownership of the widget is passed to this function.
		 * When the dialog will be destroyed, the widget and it's child widgets
		 * will be deleted.
		 * @return Any of the following result codes:
		 * - #MAW_RES_OK if the child could be added to the parent.
		 * - #MAW_RES_INVALID_LAYOUT if the widget was added to a non-layout.
		 * - #MAW_RES_ERROR if it could not be added for some other reason.
		 */
		virtual int setMainWidget(Widget* widget);

		/**
		 * Shows the dialog. Only one dialog at a time is visible.
		 * It will become visible on top of the UI.
		 */
		virtual void show();

		/**
		 * Hides a dialog if it is visible.
		 */
		virtual void hide();

        /**
         * Add an dialog event listener.
         * @param listener The listener that will receive dialog events.
         */
        virtual void addDialogListener(DialogListener* listener);

        /**
         * Remove the dialog listener.
         * @param listener The listener that receives dialog events.
         */
        virtual void removeDialogListener(DialogListener* listener);

    protected:
        /**
         * This method is called when there is an event for this widget.
         * It passes on the event to all widget's listeners.
         * @param widgetEventData The data for the widget event.
         */
        virtual void handleWidgetEvent(MAWidgetEventData* widgetEventData);

    private:
        /**
         * Array with dialog listeners.
         */
        MAUtil::Vector<DialogListener*> mDialogListeners;
	};

} // namespace NativeUI

#endif
