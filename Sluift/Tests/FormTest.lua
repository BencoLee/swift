--[[
	Copyright (c) 2013 Remko Tronçon
	Licensed under the GNU General Public License v3.
	See Documentation/Licenses/GPLv3.txt for more information.
--]]

example_form = [[
<x xmlns='jabber:x:data' type='form'>
	<title>Bot Configuration</title>
	<instructions>Fill out this form to configure your new bot!</instructions>
	<field type='hidden' var='FORM_TYPE'>
		<value>jabber:bot</value>
	</field>
	<field type='fixed'><value>Section 1: Bot Info</value></field>
	<field type='text-single' label='The name of your bot' var='botname'/>
	<field type='text-multi' label='Helpful description of your bot' var='description'/>
	<field type='boolean' label='Public bot?' var='public'>
		<required/>
	</field>
	<field type='text-private' label='Password for special access' var='password'/>
	<field type='fixed'><value>Section 2: Features</value></field>
	<field type='list-multi' label='What features will the bot support?' var='features'>
		<option label='Contests'><value>contests</value></option>
		<option label='News'><value>news</value></option>
		<option label='Polls'><value>polls</value></option>
		<option label='Reminders'><value>reminders</value></option>
		<option label='Search'><value>search</value></option>
		<value>news</value>
		<value>search</value>
	</field>
	<field type='fixed'><value>Section 3: Subscriber List</value></field>
	<field type='list-single' label='Maximum number of subscribers' var='maxsubs'>
		<value>20</value>
		<option label='10'><value>10</value></option>
		<option label='20'><value>20</value></option>
		<option label='30'><value>30</value></option>
		<option label='50'><value>50</value></option>
		<option label='100'><value>100</value></option>
		<option label='None'><value>none</value></option>
	</field>
	<field type='fixed'><value>Section 4: Invitations</value></field>
	<field type='jid-multi' label='People to invite' var='invitelist'>
		<desc>Tell all your friends about your new bot!</desc>
	</field>
</x>]]

form = sluift.from_xml(example_form)
--print(form)

-- Test form properties
assert(form['title'] == 'Bot Configuration')

-- Test boolean field
public_field = form['fields'][5]
assert(public_field['name'] == 'public')
assert(type(public_field['value']) == 'boolean')
assert(public_field['required'] == true)

-- Test multi field
features_field = form['fields'][8]
assert(features_field['name'] == 'features')
assert(type(features_field['value']) == 'table')
assert(#features_field['value'] == 2)
assert(features_field['value'][1] == 'news')
assert(features_field['value'][2] == 'search')

-- Test shortcut index
assert(form['features']['name'] == 'features')
assert(form['FORM_TYPE']['value'] == 'jabber:bot')

-- Test response form
submission = form:create_submission()
assert(#(submission.fields) == 8)
submission['description'] = 'my description'
assert(submission['description']['value'] == 'my description')
submission['type'] = 'cancel'
assert(#(submission.fields) == 8)

--print(sluift.to_xml({type = 'form', data = form}))
